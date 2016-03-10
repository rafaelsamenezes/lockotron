import cv2

def showFrame(frame):
    cv2.imshow("Frame", frame)
    cv2.waitKey(0)
    cv2.destroyWindow("Frame")

def saveFrame(frame, out):
    cv2.imwrite(out, frame)
