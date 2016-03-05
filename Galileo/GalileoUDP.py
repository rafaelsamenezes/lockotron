#!/usr/bin/python
from GalileoNetwork import *
from GalileoControl import *
import socket

udp_receive_port = 5005

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

sock.bind(("", udp_receive_port))
while True:
    data, addr = sock.recvfrom(1024)  # tamanho do buffer 1024 bytes
    if (data == 0):
        GalileoControl.openDoor
    elif (data == 1):
        GalileoControl.updateSystem
