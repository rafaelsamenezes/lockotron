#!/usr/bin/python
# -*- coding: utf-8 -*-
from lib_galileo.GalileoControl import Lock_o_tron as lock

if __name__ == "__main__":
    control = lock()
    print "Checando fechadura..."
    lock.openDoor()
    print "Checando sensor..."
    print lock.getInputMotionSensor()
    print "Checando conectividade..."
    control.getFrame()
