#!/usr/bin/env python3
from scapy.all import IP, ICMP, send, RandIP
import sys


if len(sys.argv) != 2:
    print("Usage: sudo python3 spoof.py <target_ip>")
    sys.exit(1)

target = sys.argv[1]

for _ in range(10):
    
    spoofed_ip = str(RandIP())
    
    
    packet = IP(src=spoofed_ip, dst=target) / ICMP()
    
    
    send(packet, verbose=0)
    print(f"Sent spoofed ICMP from: {spoofed_ip}")
