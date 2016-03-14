#!/usr/bin/python
# -*- coding: utf-8 -*-
from lib_galileo.GalileoControl import GalileoControl as gc
from lib_galileo.GalileoControl import Lock_o_tron as loc
import GalileoUDP as udp
import GlobalVariables as gv
import time

def setupGPIO(self):
    print 'Inicializando portas...'
    # gc.gpio_export(gv.doorGPPort)
    # gc.gpio_set_mode(gv.doorGPPort, gc.INPUT)

if __name__ == '__main__':
    control = loc()
    t1 = udp.UDPThread()
    # t1.daemon = True
    t1.start()
    try:
        while True:
            if control.getInputMotionSensor() == 1:
                print "Reconhecimento"
            elif t1.getMessage() == 0:
                control.openDoor()
                time.sleep(3)
                control.closeDoor()
    except KeyboardInterrupt:
        print "Fim do programa"
        t1.join()
