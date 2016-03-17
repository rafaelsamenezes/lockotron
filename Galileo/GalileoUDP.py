# -*- coding: utf-8 -*-
import GlobalVariables as gv
import socket
import multiprocessing
from os import getpid

class UDPThread(multiprocessing.Process):
    def __init__(self):
        multiprocessing.Process.__init__(self)
        self.message = -1
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(("", gv.udp_receive_port))

    def run(self):
        print 'Executando processo de UDP (%d)' % getpid()
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
