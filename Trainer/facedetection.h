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
    std::vector<Rect> faces;
    VideoCapture webCam;
    Mat frame;
    Mat detectedFrame;
    int savedFrames;
    void detectAndDisplay();
    void saveFrame();
public:
    FaceDetection();
    FaceDetection(int camera);
    FaceDetection(Mat frame);
    Mat getDetectedFrame();
    void readVideoFile(String video_file);
    void readWebCam();
};

#endif // FACEDETECTION_H
