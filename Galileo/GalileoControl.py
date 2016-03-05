from GalileoNetwork import GalileoNetwork as GN
import os.path
import GlobalVariables as gv

class GalileoControl:
    'This class is responsible for handling gpio and system operations from galileo'
    @staticmethod
    def openDoor():
        return 0

    @staticmethod
    def updateSystem():
        network = GN(gv.server_url)
        update = network.getFaces()
        GalileoControl.createFile('new-faces.xml', update)
        return 0

    @staticmethod
    def getFrame():
        network = GN(gv.server_url)
        frame = network.getFrame()
        GalileoControl.createFile('frame.jpg', frame)

    @staticmethod
    def createFile(file_name, contents):
        fo = open(file_name, 'wb')
        fo.write(contents)
        fo.close()

    @staticmethod
    def isUpdateAvailable():
        check = os.path.exists('new-faces.xml')
        return check
