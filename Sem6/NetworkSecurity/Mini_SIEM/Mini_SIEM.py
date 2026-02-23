#!/usr/bin/env python3
from scapy.all import *
from collections import defaultdict, deque
import time

# ================= CONFIG =================
INTERFACE = "vboxnet0"        # IMPORTANT: host-only interface
LOG_FILE = "siem.log"

ARP_THRESHOLD = 5
MAC_THRESHOLD = 20
NMAP_PORT_THRESHOLD = 15
DHCP_THRESHOLD = 8

# ================= STATE =================
arp_activity = defaultdict(int)
mac_table = set()
port_scans = defaultdict(set)
dhcp_requests = defaultdict(int)
recent_http = deque(maxlen=50)

# ================= LOGGER =================
def log(event, details):
    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
    line = f"[{timestamp}] {event} | {details}"
    print(line)
    with open(LOG_FILE, "a") as f:
        f.write(line + "\n")

# ================= DETECTIONS =================
def detect_arp(pkt):
    if pkt.haslayer(ARP) and pkt[ARP].op == 2:
        src = pkt[ARP].psrc
        arp_activity[src] += 1
        if arp_activity[src] == ARP_THRESHOLD:
            log("ARP_SPOOFING",
                f"Suspicious ARP replies from {src}")

def detect_mac_flood(pkt):
    if pkt.haslayer(Ether):
        mac = pkt[Ether].src
        mac_table.add(mac)
        if len(mac_table) == MAC_THRESHOLD:
            log("MAC_FLOODING",
                f"MAC table explosion detected ({len(mac_table)} MACs)")

def detect_nmap(pkt):
    if pkt.haslayer(TCP) and pkt.haslayer(IP):
        src = pkt[IP].src
        port_scans[src].add(pkt[TCP].dport)
        if len(port_scans[src]) == NMAP_PORT_THRESHOLD:
            log("NMAP_SCAN",
                f"Port scan from {src} → ports {list(port_scans[src])}")

def detect_dhcp(pkt):
    if pkt.haslayer(DHCP) and pkt.haslayer(BOOTP):
        mac = pkt[Ether].src
        for opt in pkt[DHCP].options:
            if opt[0] == "message-type" and opt[1] == 1:
                dhcp_requests[mac] += 1
                if dhcp_requests[mac] == DHCP_THRESHOLD:
                    log("DHCP_STARVATION",
                        f"DHCP flood from MAC {mac}")

def detect_sslstrip(pkt):
    if pkt.haslayer(TCP) and pkt.haslayer(Raw):
        try:
            payload = pkt[Raw].load.decode(errors="ignore")
            if "HTTP/1.1 301" in payload or "HTTP/1.1 302" in payload:
                if "https://" not in payload:
                    log("SSL_STRIPPING",
                        f"HTTP downgrade {pkt[IP].src} → {pkt[IP].dst}")
        except:
            pass

# ================= PACKET HANDLER =================
def handle_packet(pkt):
    detect_arp(pkt)
    detect_mac_flood(pkt)
    detect_nmap(pkt)
    detect_dhcp(pkt)
    detect_sslstrip(pkt)

# ================= MAIN =================
print(" Mini-SIEM started")
print(f" Interface: {INTERFACE}")
print(f" Logs: {LOG_FILE}")

sniff(iface=INTERFACE, prn=handle_packet, store=False)
