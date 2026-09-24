import os
import socket
import time
from datetime import datetime

CLIENT_ID = os.getenv("CLIENT_ID", "client")
MASTER_HOST = os.getenv("MASTER_HOST", "clock-master")
MASTER_PORT = 5000
CLOCK_OFFSET = float(os.getenv("CLOCK_OFFSET", "0"))


def client_clock():
    return time.time() + CLOCK_OFFSET


def show(t):
    return datetime.fromtimestamp(t).strftime("%H:%M:%S.%f")[:-3]


def connect_to_master():
    while True:
        try:
            return socket.create_connection((MASTER_HOST, MASTER_PORT))
        except OSError:
            print(f"{CLIENT_ID}: master not ready, retrying...")
            time.sleep(1)


initial_clock = client_clock()
sock = connect_to_master()

t1 = client_clock()
sock.sendall(f"TIME_REQUEST {CLIENT_ID}".encode())
master_time = float(sock.recv(1024).decode())
real_time = time.time()
t2 = real_time + CLOCK_OFFSET
sock.close()

rtt = t2 - t1
delay = rtt / 2
corrected_clock = master_time + delay

# Master's clock has offset 0, so the true time at T2 is real_time
error = corrected_clock - real_time

print(f"""
========== CRISTIAN'S ALGORITHM ==========

Client ID       : {CLIENT_ID}
Clock Offset    : {CLOCK_OFFSET:+.3f} s
Initial Clock   : {show(initial_clock)}

T1              : {show(t1)}
Master Time     : {show(master_time)}
T2              : {show(t2)}

RTT             : {rtt * 1000:.3f} ms
Estimated Delay : {delay * 1000:.3f} ms

Corrected Clock : {show(corrected_clock)}
Final Error     : {error * 1000:+.3f} ms
==========================================
""")
