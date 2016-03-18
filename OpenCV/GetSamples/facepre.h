#ifndef FACEPRE_H
#define FACEPRE_H

#include <opencv2/opencv.hpp>
using namespace cv;

class FacePre
{
private:
    bool goodFrame;
    Mat frame;
    Mat topLeft;
    Mat topRight;
    CascadeClassifier eyeDetector;
    CascadeClassifier eyeDetector2;
    Point leftEye;
    Point rightEye;
    void getEyes();
    void procEyes();
    void procMat();
    void geometricTransformation();
    void histogram();
    void finishMat();
    void smoothing();
    void ellipseMask();
public:
    FacePre() {}
    FacePre(Mat frame);
    bool isGoodFrame();
    Mat getFrame();

};

#endif // FACEPRE_H
