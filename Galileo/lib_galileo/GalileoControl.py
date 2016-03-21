# -*- coding: utf-8 -*-
from GalileoNetwork import GalileoNetwork as GN
import os.path
from os import system
import GlobalVariables as gv
import mraa

class Lock_o_tron:
    """This class is responsible for tasks from the Lock-o-tron project"""

    def __init__(self):
        self.motion_Sensor = mraa.Gpio(gv.motion_Sensor)
        self.motion_Sensor.dir(mraa.DIR_IN)
        self.doorLock_Led = mraa.Gpio(gv.doorLock_Led)
        self.doorLock_Led.dir(mraa.DIR_OUT)
        self.motion_Led = mraa.Gpio(gv.motion_Led)
        self.motion_Led.dir(mraa.DIR_OUT)
        self.recognizer_Led = mraa.Gpio(gv.recognizer_Led)
        self.recognizer_Led.dir(mraa.DIR_OUT)

    def getInputMotionSensor(self):
        value = self.motion_Sensor.read()
        self.motion_Led.write(value)
        return value

    def openDoor(self):
        self.doorLock_Led.write(1)

    def closeDoor(self):
        self.doorLock_Led.write(0)

    def recognizingStart(self):
        self.recognizer_Led.write(1)

    def recognizingStop(self):
        self.recognizer_Led.write(0)

    @staticmethod
    def updateSystem():
        print 'Sistema sendo atualizado...'
        network = GN(gv.server_url)
        try:
            update = network.getFaces()
        except Exception as e:
            print 'Erro ao atualizar o sistema (%s)', e
        else:
            GalileoControl.createFile(gv.update, update)
            print 'Sistema atualizado com sucesso'

    @staticmethod
    def getFrame():
        print 'Obtendo frame do servidor...'
        network = GN(gv.server_url)
        try:
            frame = network.getFrame()
        except Exception as e:
            print 'Erro ao obter frame (%s)', e
        else:
            GalileoControl.createFile(gv.frame, frame)
            print 'Frame obtido com sucesso'

    @staticmethod
    def isUpdateAvailable():
        print 'Verificando atualizações...'
        check = os.path.exists(gv.update)
        return check


class GalileoControl:
    """This class is responsible for handling gpio and system operations of galileo"""
    OUTPUT = 'out'
    INPUT  = 'in'
    HIGH = 1
    LOW = 0

    @staticmethod
    def change_priority(pid, priority):
        command = 'chrt -f -p %d %d' % (priority, pid)
        system(command)

    @staticmethod
    def gpio_export(gpio_num):
        fo = open(gv.gp_path + 'export', 'w')
        fo.write(str(gpio_num))
        fo.close()

    @staticmethod
    def gpio_set_mode(gpio_num, mode):
        fo = open(gv.gp_path + 'gpio' + str(gpio_num) + '/direction', 'w')
        fo.write(mode)

    @staticmethod
    def gpio_set_value(gpio_num, value):
        fo = open(gv.gp_path + 'gpio' + str(gpio_num) + '/value', 'w')
        fo.write(value)

    @staticmethod
    def gpio_get_value(gpio_num):
        fo = open(gv.gp_path + 'gpio' + str(gpio_num) + '/value', 'r')
        value = fo.read()
        return value

    @staticmethod
    def createFile(file_name, contents):
        fo = open(file_name, 'wb')
        fo.write(contents)
        fo.close()

    @staticmethod
    def renameFile(src_name, out_name):
        os.remove(out_name)
        os.rename(src_name, out_name)
