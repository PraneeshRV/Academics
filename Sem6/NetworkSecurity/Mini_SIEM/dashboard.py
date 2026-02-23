from flask import Flask, render_template_string
import os
import re

LOG_FILE = "siem.log"
app = Flask(__name__)

HTML = """
<!DOCTYPE html>
<html>
<head>
<title>Mini SIEM – SOC Events</title>
<style>
body {
    background: #0b1220;
    color: #e5e7eb;
    font-family: "Segoe UI", Arial, sans-serif;
}
.header {
    text-align: center;
    padding: 20px;
    font-size: 26px;
    font-weight: 600;
}
.container {
    width: 90%;
    margin: auto;
}
.event {
    background: #020617;
    border-left: 6px solid #334155;
    margin-bottom: 20px;
    padding: 15px 20px;
    border-radius: 6px;
}
.event.HIGH { border-color: #ef4444; }
.event.MEDIUM { border-color: #f59e0b; }
.event.LOW { border-color: #22c55e; }

.time {
    color: #94a3b8;
    font-size: 13px;
}
.attack {
    font-size: 18px;
    font-weight: 600;
    margin-top: 5px;
}
.desc {
    margin-top: 8px;
    color: #cbd5f5;
}
.fields {
    margin-top: 10px;
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
    gap: 8px;
}
.field {
    background: #020617;
    padding: 6px 10px;
    border-radius: 4px;
    font-family: monospace;
    font-size: 13px;
    color: #93c5fd;
}
.explain {
    margin-top: 12px;
    padding: 10px;
    background: #020617;
    border-left: 4px solid #38bdf8;
    color: #e5e7eb;
    font-size: 14px;
}
.footer {
    text-align: center;
    margin: 20px;
    color: #94a3b8;
}
</style>
</head>

<body>

<div class="header">🛡 Mini SIEM – SOC Events (Splunk-style)</div>

<div class="container">
{% for e in events %}
<div class="event {{e.severity}}">
    <div class="time">{{e.time}}</div>
    <div class="attack">{{e.attack}}</div>

    <div class="fields">
        <div class="field">severity={{e.severity}}</div>
        {% if e.src_ip %}<div class="field">src_ip={{e.src_ip}}</div>{% endif %}
        {% if e.dst_ip %}<div class="field">dst_ip={{e.dst_ip}}</div>{% endif %}
    </div>

    <div class="desc">{{e.description}}</div>

    <div class="explain">
        <b>Explanation:</b> {{e.explanation}}
    </div>
</div>
{% endfor %}
</div>

<div class="footer">Refresh page to update events</div>

</body>
</html>
"""

def parse_logs():
    events = []
    if not os.path.exists(LOG_FILE):
        return events

    with open(LOG_FILE, "r") as f:
        for line in f:
            line = line.strip()
            if "]" not in line or "|" not in line:
                continue

            try:
                time_part = line.split("]")[0].replace("[", "")
                rest = line.split("]")[1].strip()
                attack, description = rest.split(" | ", 1)

                # Extract IPs
                ips = re.findall(r"(?:\d{1,3}\.){3}\d{1,3}", description)
                src_ip = ips[0] if len(ips) >= 1 else None
                dst_ip = ips[1] if len(ips) >= 2 else None

                # Severity logic
                if attack in ["ARP_SPOOFING", "DHCP_STARVATION", "SSL_STRIPPING"]:
                    severity = "HIGH"
                elif attack in ["MAC_FLOODING", "NMAP_SCAN"]:
                    severity = "MEDIUM"
                else:
                    severity = "LOW"

                # Explanation mapping (SOC language)
                explanations = {
                    "ARP_SPOOFING":
                        "Multiple ARP replies detected for the same IP, indicating a possible Man-in-the-Middle attack.",
                    "MAC_FLOODING":
                        "A large number of unique MAC addresses were observed, which can overflow the switch CAM table.",
                    "NMAP_SCAN":
                        "Multiple ports were probed in a short time, a common reconnaissance technique.",
                    "DHCP_STARVATION":
                        "Excessive DHCP requests may exhaust the available IP address pool.",
                    "SSL_STRIPPING":
                        "HTTP traffic observed after MITM, suggesting HTTPS downgrade.",
                }

                events.append({
                    "time": time_part,
                    "attack": attack,
                    "description": description,
                    "src_ip": src_ip,
                    "dst_ip": dst_ip,
                    "severity": severity,
                    "explanation": explanations.get(
                        attack,
                        "Suspicious network activity detected."
                    )
                })
            except:
                pass

    return events[::-1]

@app.route("/")
def dashboard():
    return render_template_string(HTML, events=parse_logs())

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)
