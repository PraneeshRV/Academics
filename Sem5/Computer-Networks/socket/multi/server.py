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

clients, keys = {}, {}

def handle_client(c, cid):
    k = keys[cid]
    c.send(f"ASSIGNED_KEY:{k}".encode())
    print(f"[SERVER] Client {cid} connected with key {k}")
    while True:
        try:
            d = c.recv(1024).decode()
            if not d: break
            print(f"[SERVER] Raw from Client {cid}: {d}")
            if ":" not in d: continue
            tid, msg = d.split(":", 1)
            tid = int(tid)
            dec = decrypt(msg, k)
            print(f"[SERVER] Decrypted from Client {cid}: {dec}")
            if tid in clients:
                enc = encrypt(dec, keys[tid])
                clients[tid].send(enc.encode())
                c.send(f"[ACK] Delivered to Client {tid}".encode())
                print(f"[SERVER] Forwarded to Client {tid} (enc: {enc})")
            else:
                c.send(f"[ERROR] Client {tid} not connected".encode())
                print(f"[SERVER] Delivery failed: Client {tid} not connected")
        except Exception as e:
            print(f"[SERVER] Error with Client {cid}: {e}")
            break
    c.close()
    del clients[cid]
    print(f"[SERVER] Client {cid} disconnected")

s = socket.socket()
s.bind(("127.0.0.1", 5000))
s.listen()
print("[SERVER] Server started on port 5000")

cid = 1
while True:
    c, a = s.accept()
    clients[cid] = c
    keys[cid] = cid * 2 + 1
    print(f"[SERVER] Accepted connection from {a}, assigned Client ID {cid} key {keys[cid]}")
    threading.Thread(target=handle_client, args=(c, cid)).start()
    cid += 1
