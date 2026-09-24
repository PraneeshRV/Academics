import os
import socket
import threading
import time
from datetime import datetime

PORT = int(os.getenv("MASTER_PORT", "5000"))
REQUEST_DELAY = float(os.getenv("REQUEST_DELAY_MS", "0")) / 1000
REPLY_DELAY = float(os.getenv("REPLY_DELAY_MS", "0")) / 1000


def master_clock():
    return time.time()


def show(t):
    return datetime.fromtimestamp(t).strftime("%H:%M:%S.%f")[:-3]


def handle_client(conn):
    message = conn.recv(1024).decode().split()

    if len(message) == 2 and message[0] == "TIME_REQUEST":
        client_id = message[1]
        time.sleep(REQUEST_DELAY)
        master_time = master_clock()
        time.sleep(REPLY_DELAY)

        conn.sendall(str(master_time).encode())
        print(f"{client_id} -> Master : TIME_REQUEST\n"
              f"Master -> {client_id} : MASTER_TIME = {show(master_time)}")

    conn.close()


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind(("0.0.0.0", PORT))
server.listen()

print(f"Master time server listening on port {PORT}")
print(f"Artificial delay: request {REQUEST_DELAY * 1000:.0f} ms, reply {REPLY_DELAY * 1000:.0f} ms")

try:
    while True:
        conn, addr = server.accept()
        threading.Thread(target=handle_client, args=(conn,)).start()
except KeyboardInterrupt:
    print("Master shutting down")
    server.close()
