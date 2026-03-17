import marshal
import os
import sys

# Locate all pyc files logically related 
# check what we caught
for root, dirs, files in os.walk('.'):
    for n in files:
        if n.endswith('.pyc'):
            print(os.path.join(root, n))
            
# Or let's just inspect directly! 
file_path = "/home/praneesh/Praneesh/Academics/Sem6/NetworkSecurity/Presentation/dump.pyc" 
try:
    with open(file_path, "rb") as f:
         f.read()
except FileNotFoundError:
    print('Wait wait check CWD dump ...', os.getcwd())

with open("/home/praneesh/Praneesh/CTFs/KICTF/chall.pkl", "rb") as f:
    import pickle
    import base64
    import gzip
    import marshal
    data = pickle.load(f)
    decoded = base64.b85decode(data)
    decompressed = gzip.decompress(decoded)
    inner = marshal.loads(decompressed[25:])
    
# Function to find code object manually
def getcode(o):
    if type(o).__name__ == 'code': return o
    if hasattr(o, '__class__') and o.__class__.__name__ == 'code': return o
    if str(type(o)) == "<class 'code'>": return o
    return None

c = None
import traceback
if isinstance(inner, bytes):
    for i in range(100):
        try:
            o = marshal.loads(inner[i:])
            if getcode(o):
                c = o
                break
        except Exception:
            pass

if c:
    import dis
    dis.dis(c)
else:
    print("Code is none. Wait... If we look at inner[0:15]: ", inner[:15])

