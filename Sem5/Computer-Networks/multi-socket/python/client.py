import socket
import threading

def encrypt(txt, shift):
    res = ""
    for ch in txt:
        if ch.isalpha():
            base = ord('A') if ch.isupper() else ord('a')
            res += chr((ord(ch) - base + shift) % 26 + base)
        else:
            res += ch
    return res

def decrypt(txt, shift):
    return encrypt(txt, -shift)

def receive_messages(sock, key):
    while True:
        try:
            data = sock.recv(1024).decode()
            if not data or data == "Exit":
                print("\nChat ended.")
                break
            print("\nFriend:", decrypt(data, key))
        except:
            break

s = socket.socket()
s.connect(('127.0.0.1', 8080))

print(s.recv(1024).decode())
key = int(input())
s.send(str(key).encode())
print("Connected to server.\nType 'Exit' to quit.\n")

recv_thread = threading.Thread(target=receive_messages, args=(s, key), daemon=True)
recv_thread.start()

while True:
    msg = input("You: ")
    s.send(encrypt(msg, key).encode())
    if msg == "Exit":
        break

s.close()