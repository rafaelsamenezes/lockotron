import GlobalVariables as gv
from lib_galileo.GalileoControl import GalileoControl
import multiprocessing
from os import getpid
from subprocess import call

class FaceRecognizer:

    @staticmethod
    def run():
        prediction = call(['./opencv_bin/Recognizer', gv.model, gv.frame])
        print prediction
        return prediction
