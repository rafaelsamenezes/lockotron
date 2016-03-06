import cv2
import numpy as np

haarcascade_path = '/usr/local/share/OpenCV/haarcascades/'
faceHaarCascade = haarcascade_path + 'haarcascade_frontalface_alt.xml'
eyeHaarCascade = haarcascade_path + "haarcascade_eye.xml"
glassesHaarCascade = haarcascade_path + "haarcascade_eye_tree_eyeglasses.xml"

class FaceHaarcascades:
    def __init__(self):
        self.haarcascade = cv2.CascadeClassifier(faceHaarCascade)

    def getFace(self, frame):
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.equalizeHist(gray, gray)
        faces = self.haarcascade.detectMultiScale(gray, 1.1, 5, cv2.CASCADE_FIND_BIGGEST_OBJECT)
        return faces[0]

class EyeHaarcascades:
    def __init__(self):
        self.haarcascade = cv2.CascadeClassifier(eyeHaarCascade)

    def getEye(self, frame):
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.equalizeHist(gray, gray)
        eye = self.haarcascade.detectMultiScale(gray, 1.1, 5, cv2.CASCADE_FIND_BIGGEST_OBJECT)
        return eye[0]

    def getEyeVector(self, frame):
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.equalizeHist(gray, gray)
        eye = self.haarcascade.detectMultiScale(gray, 1.1, 5, cv2.CASCADE_FIND_BIGGEST_OBJECT)
        return eye

class GlassHaarcascades:
    def __init__(self):
        self.haarcascade = cv2.CascadeClassifier(glassesHaarCascade)

    def getEye(self, frame):
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.equalizeHist(gray, gray)
        eye = self.haarcascade.detectMultiScale(gray, 1.1, 5, cv2.CASCADE_FIND_BIGGEST_OBJECT)
        return eye[0]
