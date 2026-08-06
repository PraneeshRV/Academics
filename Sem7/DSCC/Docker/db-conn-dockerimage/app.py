"""
Sample database connector application: Login / Signup demo.

Exposes a small Flask UI on 0.0.0.0:8080 that demonstrates a real
app-to-database workflow using psycopg2 + PostgreSQL:

  - "/signup"  create a new user (hashed password stored in the DB)
  - "/login"   authenticate an existing user
  - "/"        dashboard shown once logged in, else redirects to /login
  - "/logout"  clear the session
  - "/health"  liveness check (always OK, no DB needed)

All connection details are read from environment variables so the same
image works against any Postgres instance. On startup the app makes sure
a "users" table exists.
"""

import os
from flask import Flask, request, redirect, url_for, session, render_template_string, flash
import psycopg2
from psycopg2 import errors as pg_errors
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = os.environ.get("SECRET_KEY", "dev-secret-change-me")

# --- Database connection details from environment variables ---
DB_CONFIG = {
    "host": os.environ.get("DB_HOST", "localhost"),
    "port": os.environ.get("DB_PORT", "5432"),
    "user": os.environ.get("DB_USER", "admin"),
    "password": os.environ.get("DB_PASSWORD", "secret"),
    "dbname": os.environ.get("DB_NAME", "mydb"),
}


def get_connection():
    """Open a new connection to the database using psycopg2."""
    return psycopg2.connect(
        host=DB_CONFIG["host"],
        port=DB_CONFIG["port"],
        user=DB_CONFIG["user"],
        password=DB_CONFIG["password"],
        dbname=DB_CONFIG["dbname"],
        connect_timeout=5,
    )


def init_db():
    """Create the users table if it doesn't exist yet. Safe to call every startup."""
    try:
        conn = get_connection()
        cur = conn.cursor()
        cur.execute(
            """
            CREATE TABLE IF NOT EXISTS users (
                id SERIAL PRIMARY KEY,
                username VARCHAR(80) UNIQUE NOT NULL,
                password_hash VARCHAR(255) NOT NULL,
                created_at TIMESTAMP DEFAULT NOW()
            );
            """
        )
        conn.commit()
        cur.close()
        conn.close()
        print("[init_db] users table ready")
    except Exception as exc:
        # DB might not be up yet on first boot; app still starts, and each
        # request will show a clear connection error until it's reachable.
        print(f"[init_db] could not initialize database yet: {exc}")


BASE_STYLE = """
<style>
  body {
    font-family: -apple-system, Segoe UI, Roboto, sans-serif;
    background: #0f1115; color: #e6e6e6;
    display: flex; justify-content: center; padding: 48px 16px; margin: 0;
  }
  .card {
    background: #171a21; border-radius: 12px; padding: 32px;
    width: 100%; max-width: 380px; box-shadow: 0 4px 24px rgba(0,0,0,0.4);
  }
  h1 { font-size: 20px; margin: 0 0 20px; }
  label { display: block; font-size: 13px; color: #9aa0aa; margin: 14px 0 6px; }
  input {
    width: 100%; padding: 10px; border-radius: 8px; border: 1px solid #2a2e38;
    background: #0f1115; color: #e6e6e6; font-size: 14px; box-sizing: border-box;
  }
  button {
    margin-top: 22px; width: 100%; padding: 10px; border: none; border-radius: 8px;
    background: #3b82f6; color: white; font-size: 14px; cursor: pointer;
  }
  button:hover { background: #2563eb; }
  .link { margin-top: 16px; font-size: 13px; text-align: center; color: #9aa0aa; }
  a { color: #60a5fa; text-decoration: none; }
  .flash { padding: 10px; border-radius: 8px; font-size: 13px; margin-bottom: 12px; }
  .flash.error { background: #341717; color: #f87171; }
  .flash.ok { background: #16321f; color: #4ade80; }
  .badge { display:inline-block; padding:6px 14px; border-radius:999px; font-weight:600; font-size:14px; background:#16321f; color:#4ade80; margin-bottom: 16px; }
</style>
"""

SIGNUP_PAGE = BASE_STYLE + """
<div class="card">
  <h1>Create an account</h1>
  {% for msg in get_flashed_messages() %}<div class="flash error">{{ msg }}</div>{% endfor %}
  <form method="post">
    <label>Username</label>
    <input name="username" required autofocus>
    <label>Password</label>
    <input type="password" name="password" required>
    <button type="submit">Sign up</button>
  </form>
  <div class="link">Already have an account? <a href="{{ url_for('login') }}">Log in</a></div>
</div>
"""

LOGIN_PAGE = BASE_STYLE + """
<div class="card">
  <h1>Log in</h1>
  {% for msg in get_flashed_messages() %}<div class="flash error">{{ msg }}</div>{% endfor %}
  <form method="post">
    <label>Username</label>
    <input name="username" required autofocus>
    <label>Password</label>
    <input type="password" name="password" required>
    <button type="submit">Log in</button>
  </form>
  <div class="link">No account yet? <a href="{{ url_for('signup') }}">Sign up</a></div>
</div>
"""

DASHBOARD_PAGE = BASE_STYLE + """
<div class="card">
  <span class="badge">&#10003; Connected to {{ dbname }}</span>
  <h1>Welcome, {{ username }}</h1>
  <p style="color:#9aa0aa; font-size:14px;">
    You're logged in. This confirms the app wrote your account to the
    <code>users</code> table in Postgres and read it back to authenticate you.
  </p>
  <form method="post" action="{{ url_for('logout') }}">
    <button type="submit">Log out</button>
  </form>
</div>
"""


@app.route("/")
def index():
    if "username" not in session:
        return redirect(url_for("login"))
    return render_template_string(
        DASHBOARD_PAGE, username=session["username"], dbname=DB_CONFIG["dbname"]
    )


@app.route("/signup", methods=["GET", "POST"])
def signup():
    if request.method == "POST":
        username = request.form["username"].strip()
        password = request.form["password"]
        try:
            conn = get_connection()
            cur = conn.cursor()
            password_hash = generate_password_hash(password)
            cur.execute(
                "INSERT INTO users (username, password_hash) VALUES (%s, %s)",
                (username, password_hash),
            )
            conn.commit()
            cur.close()
            conn.close()
            session["username"] = username
            return redirect(url_for("index"))
        except pg_errors.UniqueViolation:
            flash("That username is already taken.")
        except Exception as exc:
            flash(f"Could not reach the database: {exc}")
    return render_template_string(SIGNUP_PAGE)


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"].strip()
        password = request.form["password"]
        try:
            conn = get_connection()
            cur = conn.cursor()
            cur.execute(
                "SELECT password_hash FROM users WHERE username = %s", (username,)
            )
            row = cur.fetchone()
            cur.close()
            conn.close()
            if row and check_password_hash(row[0], password):
                session["username"] = username
                return redirect(url_for("index"))
            flash("Invalid username or password.")
        except Exception as exc:
            flash(f"Could not reach the database: {exc}")
    return render_template_string(LOGIN_PAGE)


@app.route("/logout", methods=["POST"])
def logout():
    session.pop("username", None)
    return redirect(url_for("login"))


@app.route("/health")
def health():
    return {"status": "ok"}


# Try to create the table as soon as the app starts.
init_db()

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)