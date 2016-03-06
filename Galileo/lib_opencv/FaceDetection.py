import Haarcascades as h
import cv2

class FaceDetection:
    @staticmethod
    def detectAndDisplay(frame):
        fh = h.FaceHaarcascades()
        x, y, w, h = fh.getFace(frame)
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 3)
        imshow("Detectedframe", frame)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
