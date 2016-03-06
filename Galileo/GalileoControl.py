from GalileoNetwork import GalileoNetwork as GN
import os.path
import GlobalVariables as gv

class GalileoControl:
    """This class is responsible for handling gpio and system operations of galileo"""
    OUTPUT = 'out'
    INPUT  = 'in'
    HIGH = 1
    LOW  = 0

    @staticmethod
    def gpio_export(gpio_num):
        fo = open(gv.gp_path + 'export', 'w')
        fo.write(gpio_num)
        fo.close()

    @staticmethod
    def gpio_set_mode(gpio_num, mode):
        fo = open(gv.gp_path + 'gpio' + gpio_num + '/direction', 'w')
        fo.write(mode)

    @staticmethod
    def gpio_set_value(gpio_num, value):
        fo = open(gv.gp_path + 'gpio' + gpio_num + '/value', 'w')
        fo.write(value)

    @staticmethod
    def gpio_get_value(gpio_num):
        fo = open(gv.gp_path + 'gpio' + gpio_num + '/value', 'r')
        value = fo.read()
        return value

    @staticmethod
    def openDoor():
        gpio_set_value(gv.doorLock, gv.HIGH)
        servoOpen()

    @staticmethod
    def updateSystem():
        network = GN(gv.server_url)
        update = network.getFaces()
        GalileoControl.createFile(gv.update, update)

    @staticmethod
    def getFrame():
        network = GN(gv.server_url)
        frame = network.getFrame()
        GalileoControl.createFile(gv.frame, frame)

    @staticmethod
    def createFile(file_name, contents):
        fo = open(file_name, 'wb')
        fo.write(contents)
        fo.close()

    @staticmethod
    def servoOpen():
        pass

    def servoClose():
        pass

    @staticmethod
    def renameFile(src_name, out_name):
        fi = open(src_name, 'rb')
        data = fi.read()
        fi.close()
        createFile(out_name, data)
        os.remove(src_name)

    @staticmethod
    def isUpdateAvailable():
        check = os.path.exists(gv.update)
        return check
