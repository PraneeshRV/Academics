import socket
import datetime
import time
import os

def start_client():
    s = socket.socket()
    server_host = os.environ.get('SERVER_HOST', 'localhost')
    server_port = 8000

    print(f"Connecting to {server_host}:{server_port}...")
    time.sleep(1) 
    request_time = datetime.datetime.now()
    s.connect((server_host, server_port))
    
    server_time_str = s.recv(1024).decode()
    
    response_time = datetime.datetime.now()
    
    server_time = datetime.datetime.strptime(server_time_str, "%Y-%m-%d %H:%M:%S.%f")
    
    rtt = (response_time - request_time).total_seconds()
    
    synchronized_time = server_time + datetime.timedelta(seconds=(rtt / 2))
    
    print(f"Time received from server: {server_time}")
    print(f"Round Trip Time (RTT):     {rtt} seconds")
    print(f"Calculated Sync Time:      {synchronized_time}")
    
    s.close()

if __name__ == '__main__':
    start_client()
