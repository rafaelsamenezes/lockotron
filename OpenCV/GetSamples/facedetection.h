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
    std::vector<Rect> old_faces;
    VideoCapture webCam;
    Mat frame;
    Mat old_frame;
    Mat detectedFrame;
    int savedFrames;
    string save_path;
    double getSimilarity(const Mat A, const Mat B);
    void detectAndDisplay();
    void saveFrame(FacePre frame);
public:

    FaceDetection(int camera, string path);
    Mat getDetectedFrame();
    void readWebCam();
};

#endif // FACEDETECTION_H
