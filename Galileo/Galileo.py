#!/usr/bin/python
# -*- coding: utf-8 -*-
from lib_galileo.GalileoControl import GalileoControl as gc
from lib_galileo.GalileoControl import Lock_o_tron as loc
import lib_galileo.GalileoNetwork as gn
import GalileoUDP as udp
from GalileoFaceRecognizer import FaceRecognizer as fr
import GlobalVariables as gv
import time
from os import getpid

def setupGPIO(self):
    print 'Inicializando portas...'
    # gc.gpio_export(gv.doorGPPort)
    # gc.gpio_set_mode(gv.doorGPPort, gc.INPUT)

if __name__ == '__main__':
    gc.change_priority(getpid(), gv.main_script_priority)
    control = loc()
    t1 = udp.UDPThread()
    # t1.daemon = True
    t1.start()
    network = gn.GalileoNetwork(gv.server_url)
    try:
        while True:
            if (control.getInputMotionSensor() == 1):
                loc.getFrame()
                result = fr.run()
                # result = 0
                authorization = network.askPermission(result)
                if (authorization):
                    print "Acesso Permitido"
                    loc.openDoor()
                    time.sleep(3)
                    loc.closeDoor()
    except KeyboardInterrupt:
        print "Fim do programa"
        t1.join()
