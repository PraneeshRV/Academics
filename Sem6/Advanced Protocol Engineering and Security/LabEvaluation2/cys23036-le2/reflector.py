
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
