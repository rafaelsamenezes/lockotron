#include "facedetection.h"
#include <opencv2/core.hpp>

int main(){
    FaceDetection fd(1);
    fd.readWebCam();

}
