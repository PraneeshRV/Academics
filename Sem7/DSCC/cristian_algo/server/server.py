import socket
import datetime

def start_server():
    s = socket.socket()
    s.bind(('0.0.0.0', 8000))
    s.listen(5)
    print("Server listening on port 8000...")
    
    while True:
        conn, addr = s.accept()
        server_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
        conn.send(server_time.encode())
        conn.close()

if __name__ == '__main__':
    start_server()
