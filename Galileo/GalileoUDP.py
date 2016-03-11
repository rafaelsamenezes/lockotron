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
            self.message, addr = self.sock.recvfrom(1024)
            if (self.message == 0):
                print('Servidor UDP recebeu mensagem de abrir porta')
            elif (self.message == 1):
                print('Servidor UDP recebeu mensagem de atualização')

    def getMessage(self):
        return self.message
