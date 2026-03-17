import marshal
import gzip
import base64
import sys

# Try parsing manually 
c = "d\x00d\x01\x04\x00\r\x00\x01\x00\x02\x00"

with open("/home/praneesh/Praneesh/CTFs/KICTF/chall.pkl", "rb") as f:
    import pickle
    data = pickle.load(f)
    dec = gzip.decompress(base64.b85decode(data))

# Try uncompyle6 directly
with open("dump.pyc", "wb") as f:
    f.write(dec)

