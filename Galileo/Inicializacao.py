#!/usr/bin/python
# -*- coding: utf-8 -*-
from lib_galileo.GalileoControl import Lock_o_tron as lock

if __name__ == "__main__":
    control = lock()
    control.closeDoor()
    control.recognizingStop()
