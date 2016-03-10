import os

frame = 'frame.jpg'
class RecognizeFace:

    @staticmethod
    def predict():
        print 'Verificando pessoa...'
        prediction = os.system('./facerecognizer ../{frame}'.format(frame=frame))
        good = RecognizeFace.__isGoodPrediction()
        return int(prediction), good

    @staticmethod
    def __isGoodPrediction():
        return True
