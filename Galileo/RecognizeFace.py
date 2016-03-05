import numpy as np
import GlobalVariables as gv
from GalileoControl import GalileoControl as GC
from GalileoNetwork import GalileoNetwork as GN
import cv2

GC.getFrame()
img = cv2.imread(gv.frame, 0)
cv2.imshow('image', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
