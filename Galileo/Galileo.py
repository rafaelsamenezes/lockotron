#!/usr/bin/python
from lib_galileo.GalileoControl import GalileoControl as gc
import GalileoUDP as udp_thread
import GalileoFaceRecognizer as fr_thread
import GlobalVariables as gv

def setupGPIO(self):
    print 'Inicializando portas...'
    # gc.gpio_export(gv.doorGPPort)
    # gc.gpio_set_mode(gv.doorGPPort, gc.INPUT)

if __name__ == '__main__':
    setupGPIO()
    t1, t2 = udp_thread.UDPThread(), fr_thread.GalileoFaceRecognizerThread()
    t1.start()
    t1.daemon = True
    while True:
        if (gc.gpio_get_value(gv.motionDetector == gc.HIGH) and (not t2.is_alive())):
            t2 = fr_thread.GalileoFaceRecognizerThread()
            t2.start()
        elif (t1.isMessageReceived() or gc.gpio_get_value(gv.motionDetector == gc.LOW)):
            # t2.stop() Arrumar isso
            t2.join()
