import numpy as np
import GlobalVariables as gv
import cv2

class RecognizeFace:

    def __init__(self, num):
        if (num == 1):
            self.model = cv2.face.createEigenFaceRecognizer()
        elif (num == 2):
            self.model = cv2.face.createFisherFaceRecognizer()
        else:
            self.model = cv2.face.createLBPHFaceRecognizer()

    def load(self, file):
        self.model.load(file)

    def save(self, file):
        self.model.save(file)

    def train(self, num_labels, path, num_img):
        images = list()
        labels = list()
        for i in num_labels:
            for j in range(0, num_img):
                img = cv2.imread(path+str(i)+'/frame'+str(j)+'.jpg')
                images.append(img)
                labels.append(int(i))
        l = np.array(labels)
        self.model.train(images, l)

    def predict(self, frame):
        f = cv2.imread(frame, cv2.COLOR_BGR2GRAY)
        return self.model.predict(f)

    def isGoodPrediction(self, frame):
        W = self.model.getEigenVectors()
        mean = self.model.getMean()
        face = cv2.imread(frame, cv2.COLOR_BGR2GRAY)
