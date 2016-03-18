#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "facepre.h"

using namespace cv;
class FaceDetection
{
private:
    CascadeClassifier faceCascade;

    VideoCapture webCam;
    Mat frame;
    Mat detectedFrame;
    int savedFrames;

    void saveFrame();
public:
  std::vector<Rect> faces;
  void detectAndDisplay();
    FaceDetection();
    FaceDetection(int camera);
    FaceDetection(Mat frame);
    Mat getDetectedFrame();
    void readVideoFile(String video_file);
    void readWebCam();
};

#endif // FACEDETECTION_H
