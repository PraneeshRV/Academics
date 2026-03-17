import pickle
import base64
import gzip
import marshal
import types
import dis

with open("/home/praneesh/Praneesh/CTFs/KICTF/chall.pkl", "rb") as f:
    data = pickle.load(f)

decoded = base64.b85decode(data)
decompressed = gzip.decompress(decoded)
inner = marshal.loads(decompressed[25:])

def search_code(obj):
    if isinstance(obj, types.CodeType):
        print("Found Code Object!")
        dis.dis(obj)
        return obj
    elif isinstance(obj, tuple):
        for item in obj:
            res = search_code(item)
            if res:
                return res
    if hasattr(obj, "co_consts"):
        return search_code(obj.co_consts)
    return None

search_code(inner)

if isinstance(inner, types.CodeType):
    print("Inner is Code Type")
else:
    print(f"Inner type: {type(inner)}")
    
    # Check if there are code objects inside the constants of the bytecode object?
    
