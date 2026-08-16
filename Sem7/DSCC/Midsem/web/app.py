import os
import pymysql
from flask import Flask, render_template, request, redirect, session

app = Flask(__name__, template_folder=".")
app.secret_key = "123"

def get_db():
    try:
        return pymysql.connect(
            host=os.environ.get("DB_HOST", "127.0.0.1"),
            user=os.environ.get("DB_USER", "midterm_user"),
            password=os.environ.get("DB_PASSWORD", "midterm_pass"),
            database=os.environ.get("DB_NAME", "midterm_db")
        )
    except:
        return None

@app.route("/", methods=["GET", "POST"])
@app.route("/login", methods=["GET", "POST"])
def login():
    msg = ""
    if request.method == "POST":
        u = request.form.get("username")
        p = request.form.get("password")
        conn = get_db()
        if conn:
            cur = conn.cursor()
            cur.execute("SELECT full_name FROM users WHERE username=%s AND password=%s", (u, p))
            user = cur.fetchone()
            conn.close()
            if user:
                session["user"] = user[0]
                return redirect("/dashboard")
            msg = "Invalid credentials"
        else:
            msg = "Database connection error"
    return render_template("login.html", msg=msg, roll_no=os.environ.get("ROLLNUMBER", "CB.SC.U4CYS23036"), student_name=os.environ.get("NAME", "Praneesh R V"))

@app.route("/dashboard")
def dashboard():
    if "user" not in session:
        return redirect("/login")
    conn = get_db()
    users = []
    status = "Connected"
    if conn:
        cur = conn.cursor()
        cur.execute("SELECT id, username, full_name, role FROM users")
        users = cur.fetchall()
        conn.close()
    else:
        status = "Failed"
    return render_template(
        "dashboard.html",
        user=session["user"],
        users=users,
        db_status=status,
        roll_no=os.environ.get("ROLLNUMBER", "CB.SC.U4CYS23036"),
        student_name=os.environ.get("NAME", "Praneesh R V")
    )

@app.route("/logout")
def logout():
    session.clear()
    return redirect("/login")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
