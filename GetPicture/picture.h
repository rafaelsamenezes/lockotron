#ifndef PICTURE_H
#define PICTURE_H

#include <opencv2/opencv.hpp>
#include "timer.h"
using namespace std;
using namespace cv;
class Picture
{
private:
    VideoCapture cv;
public:
    Picture(int camera);
    Picture();
    void begin(string path);
};

#endif // PICTURE_H
