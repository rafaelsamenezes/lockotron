import cv2
import numpy as np
import Haarcascades as h


class FacePreProcessing:
    EYE_SX = 0.16
    EYE_SY = 0.26
    EYE_SW = 0.30
    EYE_SH = 0.28
    DESIRED_LEFT_EYE_X = 0.16
    DESIRED_RIGHT_EYE_X = (1.0 - 0.16)
    DESIRED_FACE_WIDTH = 70
    DESIRED_FACE_HEIGHT = 70

    @staticmethod
    def preProcessFrame(frame):
        gray = FacePreProcessing.__initializeFrame(frame)
        topLeft, topRight = FacePreProcessing.__getEyes(gray)
        lp, rp, status = FacePreProcessing.__procEyes(topLeft, topRight, gray)
        if (status):
            result = FacePreProcessing.__finishMat(lp, rp, gray)
            return result, status
        return frame, status

    @staticmethod
    def __initializeFrame(frame):
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.equalizeHist(gray, gray)
        return gray

    @staticmethod
    def __getEyes(frame):
        leftX = cv2.cvRound(frame.cols * FacePreProcessing.EYE_SX)
        topY = cv2.cvRound(frame.rows * FacePreProcessing.EYE_SY)
        widthX = cv2.cvRound(frame.cols * FacePreProcessing.EYE_SW)
        heightY = cv2.cvRound(frame.rows * FacePreProcessing.EYE_SH)
        rightX = cv2.cvRound(frame.cols * (1.0 - FacePreProcessing.EYE_SX - FacePreProcessing.EYE_SW))
        topLeft = frame(cv2.Rect(leftX, topY, widthX, heightY))
        topRight = frame(cv2.Rect(rightX, topY, widthX, heightY))
        return topLeft, topRight

    @staticmethod
    def __procEyes(topLeft, topRight, frame):
        leftX = cv2.cvRound(frame.cols * FacePreProcessing.EYE_SX)
        topY = cv2.cvRound(frame.rows * FacePreProcessing.EYE_SY)
        rightX = cv2.cvRound(frame.cols * (1.0 - FacePreProcessing.EYE_SX - FacePreProcessing.EYE_SW))
        leftEyeFound, rightEyeFound = False, False

        eyeDetector = h.EyeHaarcascades()
        glassDetector = h.GlassHaarcascades()

        vec = eyeDetector.getEyeVector(topLeft)
        lex, ley = 0, 0
        for (x, y, h, w) in vec:
            rightEyeFound = True
            lex = x + w/2 + leftX
            ley = y + h/2 + topY
        if (not rightEyeFound):
            vec = glassDetector.getEyeVector(topLeft)
            for (x, y, h, w) in vec:
                rightEyeFound = True
                lex = x + w/2 + leftX
                ley = y + h/2 + topY

        vec = eyeDetector.getEyeVector(topRight)
        rex, rey = 0, 0
        for (x, y, h, w) in vec:
            rightEyeFound = True
            rex = x + w/2 + leftX
            rey = y + h/2 + topY
        if (not rightEyeFound):
            vec = glassDetector.getEyeVector(topRight)
            for (x, y, h, w) in vec:
                rightEyeFound = True
                rex = x + w/2 + rightX
                rey = y + h/2 + topY

        return (lex, ley), (rex, rey), (leftEyeFound and rightEyeFound)

    @staticmethod
    def __finishMat(lp, rp, frame):
        warped = FacePreProcessing.__geometricTransformation(lp, rp, frame)
        


    @staticmethod
    def __geometricTransformation((lex, ley), (rex, rey), frame):
        eyesCenter = ((lex + rex)*0.5, (rey + ley)*0.5)
        dx, dy = rex - lex, rey - ley
        len = cv2.sqrt(dx*dx + dy*dy)
        angle = cv2.fastAtan2(dy, dx) * 180/np.pi
        desiredLen = FacePreProcessing.DESIRED_RIGHT_EYE_X - 0.16
        scale = desiredLen/len
        rot_mat = cv2.getRotationMatrix2D(eyesCenter, angle, scale)
        ex = FacePreProcessing.DESIRED_FACE_WIDTH * 0.5 - eyesCenter[0]
        ey = FacePreProcessing.DESIRED_FACE_HEIGHT & 0.14 - eyesCenter[1]
        p = (FacePreProcessing.DESIRED_FACE_HEIGHT, FacePreProcessing.DESIRED_FACE_WIDTH)
        rot_mat[0][2] += ex
        rot_mat[1][2] += ey
        warped = cv2.warpAffine(frame, rot_mat, p)
        return warped
