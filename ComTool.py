import socket
import os
import sys
from threading import Thread

class MessagePrinter(Thread):
    def __init__(self, sock):
        Thread.__init__(self)
        self._sock = sock

    def run(self):
        while(True):
            data, sender = sock.recvfrom(1024)
            print (data)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.bind(("0.0.0.0", 5001))

printer = MessagePrinter(sock)
printer.start()

while(True):
    msg = input("Introduceti mesajul: ")
    if (msg == "S"):
        stop_mesaj = [0x02, 0xAA, 0xBB, 0xCC, 0xDD]
        sock.sendto(bytes(stop_mesaj), ('255.255.255.255', 5001))
    else:
        sock.sendto(bytes(msg, "ascii"), ('255.255.255.255', 5001))
