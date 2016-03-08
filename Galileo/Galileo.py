#!/usr/bin/python
from lib_galileo.GalileoControl import GalileoControl as gc
from lib_galileo.GalileoControl import Lock_o_tron as loc
from lib_galileo.GalileoNetwork import GalileoNetwork as gn
from lib_opencv.RecognizeFace import RecognizeFace as rf
import GlobalVariables as gv
import GalileoUDP as udp_thread
import GalileoFaceRecognizer as fr_thread
import time

def setupGPIO(self):
    gc.gpio_export(gv.doorGPPort)
    gc.gpio_set_mode(gv.doorGPPort, gc.INPUT)

if __name__ == '__main__':
    setupGPIO()
    t1, t2 = udp_thread.UDPThread(), fr_thread.GalileoFaceRecognizerThread()
    t1.start()
    t1.daemon = True
    while True:
        if (gc.gpio_get_value(gv.motionDetector == gc.HIGH) and (not t2.is_alive())):
            pass
        elif (t1.isMessageReceived()):
            pass
