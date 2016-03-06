import cv2
from FacePreProcessing import FacePreProcessing as fpp
import Haarcascades as h

def showFrame(frame):
    cv2.imshow("Frame", frame)
    cv2.waitKey(0)
    cv2.destroyWindow("Frame")

def saveFrame(frame, out):
    cv2.imwrite(out, frame)
