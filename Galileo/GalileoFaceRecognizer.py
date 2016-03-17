import os
import GlobalVariables as gv
import GalileoControl from lib_galileo.GalileoControl
import multiprocessing
from os import getpid

class FaceRecognizer:

    @staticmethod
    def run(self):
        prediction = os.system('./opencv_bin/facerecognizer {frame}'.format(frame=gv.frame))
        return (int(prediction)/10)
