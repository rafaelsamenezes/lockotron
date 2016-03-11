# -*- coding: utf-8 -*-
import GlobalVariables as gv
import socket
import threading

class UDPThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        print('Inicializando thread de UDP')
        self.message = -1
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(("", gv.udp_receive_port))

    def run(self):
        while True:
            msg, addr = self.sock.recvfrom(1024)
            self.message = ord(msg)
            print type(self.message), addr
            if (self.message == 0):
                print('Servidor UDP recebeu mensagem de abrir porta')
            elif (self.message == 1):
                print('Servidor UDP recebeu mensagem de atualização')
            elif (len(msg) > 0):
                print('Recebi mensagem inválida')
                break

    def getMessage(self):
        a = self.message
        self.message = -1
        return a
