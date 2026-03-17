import pickle
import base64
import gzip
import marshal
from inspect import getmembers

with open("/home/praneesh/Praneesh/CTFs/KICTF/chall.pkl", "rb") as f:
    data = pickle.load(f)

decoded = base64.b85decode(data)
decompressed = gzip.decompress(decoded)

inner = marshal.loads(decompressed[25:])
print("Inner:", type(inner))
import sys
sys.stdout.flush()

def find_code(obj):
    if type(obj).__name__ == 'code':
        return obj
    elif isinstance(obj, bytes):
        for i in range(100):
            try:
                candidate = marshal.loads(obj[i:])
                if type(candidate).__name__ == 'code':
                    return candidate
            except:
                continue
    return None

c = find_code(inner)
if c:
    with open('/home/praneesh/Praneesh/Academics/Sem6/NetworkSecurity/Presentation/dumped_ctf.pyc', 'wb') as f:
        f.write(c)
    print("Code object found.")
else:
    print("Not found.")
