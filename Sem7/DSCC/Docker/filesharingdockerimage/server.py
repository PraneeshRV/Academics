import os
import json
from flask import Flask, request, redirect, url_for, send_from_directory, render_template_string

app = Flask(__name__)

# ---- Load configuration ----
with open("config.json") as f:
    config = json.load(f)

# Environment variables take priority over config.json defaults
UPLOAD_DIR = os.environ.get("UPLOAD_DIR", config.get("upload_dir", "/app/uploads"))
APP_PORT = int(os.environ.get("APP_PORT", config.get("app_port", 8000)))
APP_ENV = os.environ.get("APP_ENV", config.get("app_env", "production"))

os.makedirs(UPLOAD_DIR, exist_ok=True)

PAGE_TEMPLATE = """
<!doctype html>
<html>
<head>
    <title>Internal File Sharing Service</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; background: #f4f6f8; }
        h1 { color: #2c3e50; }
        .badge { background: #2980b9; color: white; padding: 3px 10px; border-radius: 10px; font-size: 12px; }
        ul { line-height: 1.8; }
        form { margin: 20px 0; padding: 15px; background: #fff; border-radius: 8px; width: fit-content; }
    </style>
</head>
<body>
    <h1>Internal File Sharing Service <span class="badge">{{ env }}</span></h1>

    <form method="post" action="/upload" enctype="multipart/form-data">
        <input type="file" name="file">
        <input type="submit" value="Upload">
    </form>

    <h2>Available Files</h2>
    <ul>
    {% for f in files %}
        <li>{{ f }} — <a href="/view/{{ f }}">View</a> | <a href="/download/{{ f }}">Download</a></li>
    {% else %}
        <li>No files uploaded yet.</li>
    {% endfor %}
    </ul>
</body>
</html>
"""

VIEW_TEMPLATE = """
<!doctype html>
<html>
<head>
    <title>{{ filename }} - Internal File Sharing Service</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; background: #f4f6f8; }
        h1 { color: #2c3e50; font-size: 20px; }
        pre { background: #fff; padding: 15px; border-radius: 8px; white-space: pre-wrap; word-wrap: break-word; }
        a { color: #2980b9; }
    </style>
</head>
<body>
    <p><a href="/">&larr; Back to file list</a></p>
    <h1>{{ filename }}</h1>
    {% if is_text %}
        <pre>{{ content }}</pre>
    {% else %}
        <p>This file can't be displayed as text (likely binary).
           <a href="/download/{{ filename }}">Download it instead</a>.</p>
    {% endif %}
</body>
</html>
"""

@app.route("/")
def home():
    files = sorted(os.listdir(UPLOAD_DIR))
    return render_template_string(PAGE_TEMPLATE, files=files, env=APP_ENV)

@app.route("/upload", methods=["POST"])
def upload_file():
    file = request.files.get("file")
    if file and file.filename:
        file.save(os.path.join(UPLOAD_DIR, file.filename))
    return redirect(url_for("home"))

@app.route("/view/<path:filename>")
def view_file(filename):
    filepath = os.path.join(UPLOAD_DIR, filename)
    if not os.path.isfile(filepath):
        return "File not found", 404

    # Cap how much we read/display so a huge file doesn't hang the page
    max_bytes = 200_000
    try:
        with open(filepath, "rb") as f:
            raw = f.read(max_bytes)
        content = raw.decode("utf-8")
        is_text = True
    except UnicodeDecodeError:
        content = None
        is_text = False

    return render_template_string(
        VIEW_TEMPLATE, filename=filename, content=content, is_text=is_text
    )

@app.route("/download/<path:filename>")
def download_file(filename):
    return send_from_directory(UPLOAD_DIR, filename, as_attachment=True)

@app.route("/files")
def list_files():
    return {"files": sorted(os.listdir(UPLOAD_DIR))}

@app.route("/health")
def health():
    return {"status": "ok", "environment": APP_ENV, "upload_dir": UPLOAD_DIR}

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=APP_PORT)
