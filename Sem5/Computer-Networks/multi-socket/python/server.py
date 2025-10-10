import socket

def encrypt(txt,shift):
    res = ""
    for ch in txt:
        if ch.isalpha():
            base=ord('A') if ch.isupper() else ord('a')
            res+=chr((ord(ch)-base+shift)%26+base)
        else:
            res+=ch
    return res

def decrypt(txt,shift):
    return encrypt(txt,-shift)

s=socket.socket()
s.bind(('127.0.0.1',8080))
s.listen(2)
print("Server ready...")

# Accept two clients
c1,addr1=s.accept()
print("Client1 connected:",addr1)
c1.send("Enter your key:".encode())
key1=int(c1.recv(1024).decode())

c2,addr2=s.accept()
print("Client2 connected:",addr2)
c2.send("Enter your key:".encode())
key2=int(c2.recv(1024).decode())

print(f"Client1 key={key1}, Client2 key={key2}")

while True:
    data=c1.recv(1024).decode()
    if not data or data=="Exit":
        c2.send("Exit".encode())
        print("Chat ended")
        break
    msg=decrypt(data,key1)
    print("From Client1 (decrypted):",msg)
    enc=encrypt(msg,key2)
    c2.send(enc.encode())

    # ---- Client2 to Client1 ----
    data=c2.recv(1024).decode()
    if not data or data=="Exit":
        c1.send("Exit".encode())
        print("Chat ended")
        break
    msg=decrypt(data,key2)
    print("From Client2 (decrypted):",msg)
    enc=encrypt(msg,key1)
    c1.send(enc.encode())

c1.close()
c2.close()
s.close()