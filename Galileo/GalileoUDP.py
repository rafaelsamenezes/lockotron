from lib_galileo.GalileoControl import Lock_o_tron as loc
import GlobalVariables as gv
import socket
import threading

class UDPThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        print('Inicializando thread de UDP')
        self.gotMessage = False
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(("", gv.udp_receive_port))

    def run(self):
        while True:
            data, addr = self.sock.recvfrom(1024)
            if (data == 0):
                print('Servidor UDP recebeu mensagem de abrir porta')
                self.gotMessage = True
                loc.openDoor()
            elif (data == 1):
                print('Servidor UDP recebeu mensagem de atualização')
                self.gotMessage = True
                loc.updateSystem()

    def isMessageReceived(self):
        temp = self.gotMessage
        self.gotMessage = False
        return temp
