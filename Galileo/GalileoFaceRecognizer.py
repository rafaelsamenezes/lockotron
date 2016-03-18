import os
import GlobalVariables as gv
from lib_galileo.GalileoControl import GalileoControl
import multiprocessing
from os import getpid

class FaceRecognizer:

    @staticmethod
    def run():
        prediction = os.system('./opencv_bin/Recognizer {faces} {frame}'.format(faces=gv.model , frame=gv.frame))
        print prediction
        return (int(prediction)/10)
