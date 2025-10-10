import socket, threading

def encrypt(t, k):
    r = ""
    for c in t:
        if c.isalpha():
            s = 65 if c.isupper() else 97
            r += chr((ord(c) - s + k) % 26 + s)
        else:
            r += c
    return r

def decrypt(t, k): return encrypt(t, -k)

def recv(sock, k):
    while True:
        try:
            d = sock.recv(1024).decode()
            if not d: break
            if d.startswith("ASSIGNED_KEY:"): continue
            if d.startswith("["):  # ACK or ERROR
                print(d)
            else:
                print("\n[Received]", decrypt(d, k))
        except: break

c = socket.socket()
c.connect(("127.0.0.1", 5000))
msg = c.recv(1024).decode()
k = int(msg.split(":")[1])
print(f"[CLIENT] Connected, assigned key: {k}")

threading.Thread(target=recv, args=(c, k)).start()
while True:
    tid = input("Target ID: ")
    m = input("Message: ")
    enc = encrypt(m, k)
    print(f"[CLIENT] Sending encrypted: {enc}")
    c.send(f"{tid}:{enc}".encode())
