# -*- coding: utf-8 -*-
import GlobalVariables as gv
import GalileoControl from lib_galileo.GalileoControl
from lib_galileo.GalileoControl import Lock_o_tron as loc
import socket
import multiprocessing
from os import getpid

class UDPThread(multiprocessing.Process):
    def __init__(self):
        multiprocessing.Process.__init__(self)
        self.__control = loc()
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(("", gv.udp_receive_port))

    def run(self):
        print 'Executando processo de UDP (%d)' % getpid()
        GalileoControl.change_priority(getpid(), gv.udp_server_priority)
        while True:
            msg, addr = self.sock.recvfrom(1024)
            self.message = ord(msg)
            print type(self.message), addr
            if (self.message == 0):
                print('Servidor UDP recebeu mensagem de abrir porta')
                self.__control.openDoor()
            elif (self.message == 1):
                print('Servidor UDP recebeu mensagem de atualização')
                self.__control.updateSystem()
            elif (len(msg) > 0):
                print('Servidor UDP recebeu mensagem inválida')
                break
