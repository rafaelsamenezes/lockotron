#!/usr/bin/python
from lib_galileo.GalileoControl import GalileoControl as gc
from lib_galileo.GalileoNetwork import GalileoNetwork as gn
from lib_opencv.RecognizeFace import RecognizeFace as rf
import GlobalVariables as gv
import time

def checkUpdate():
    if(gc.isUpdateAvailable()):
        gc.renameFile(gv.update, gv.model)

def checkPerson(person_id):
    conn = gn.GalileoNetwork(gv.server_url)
    return conn.askPermission(person_id)

def setupGPIO():
    gc.gpio_export(gv.doorGPPort)
    gc.gpio_export(gv.motionDetector)
    gc.gpio_export(gv.servo)
    gc.gpio_set_mode(gv.doorGPPort, gc.INPUT)
    gc.gpio_set_mode(gv.motionDetector, gc.OUTPUT)
    gc.gpio_set_mode(gv.servo, gc.OUTPUT)

def checkMotion():
    value = gc.gpio_get_value(gv.motionDetector)
    return value

if __name__ == '__main__':
    checkUpdate()
    setupGPIO()
    recognizer = rf.RecognizeFace()
    while(True):
        time.sleep(1)
        if(checkMotion == gc.HIGH):
            gc.getFrame()
            prediction = rf.predict()
            if (rf.isGoodPrediction(prediction) and checkPerson(prediction)):
                gc.openDoor()
