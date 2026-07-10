import os
import time
import datetime

os.makedirs("/data", exist_ok=True)

while True:
    timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open("/data/log.txt", "a") as f:
        f.write(timestamp + "\n")
    time.sleep(5)
