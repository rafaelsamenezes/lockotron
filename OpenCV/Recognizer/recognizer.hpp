#ifndef TRAINER_H
#define TRAINER_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/face.hpp>

#define TRAINER_FISHERFACE 0
#define TRAINER_EIGENFACE 1
#define TRAINER_LBPH 2


using namespace cv;
using namespace face;
using namespace std;
class Recognizer
{
private:
    Ptr<BasicFaceRecognizer> model;
    Mat frame;
    bool isGoodRecognition(Mat frame, int p);
    double getSimilarity(Mat a, Mat b);
    void load(string path_xml);
public:
    Recognizer(string path_frame, string path_xml);
    int recognize();
};

#endif
