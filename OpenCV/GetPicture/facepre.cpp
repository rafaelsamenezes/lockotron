#include "facepre.h"
#include "haarcascade.h"
#include <iostream>

#define EYE_SX 0.16
#define EYE_SY 0.26
#define EYE_SW 0.30
#define EYE_SH 0.28
#define DESIRED_LEFT_EYE_X 0.16
#define DESIRED_RIGHT_EYE_X (1.0f - 0.16)
#define DESIRED_FACE_WIDTH 70
#define DESIRED_FACE_HEIGHT 70

using namespace std;
FacePre::FacePre(Mat frame){
    if(frame.empty()){
        cerr << "ERROR: FacePre, empty frame!" << endl;
        exit(-1);
    }

    if(!this->eyeDetector.load( HaarCascade::eyeHaarCascade ) ){
       cerr << "ERROR: Eye HaarCascade " << HaarCascade::eyeHaarCascade << " couldn't be loaded!" << endl;
       exit(-1);
    }

    if(!this->eyeDetector2.load( HaarCascade::glassesHaarCascade ) ){
       cerr << "ERROR: Glasses HaarCascade " << HaarCascade::glassesHaarCascade << " couldn't be loaded!" << endl;
       exit(-1);
    }

    this->goodFrame = false;
    frame.copyTo(this->frame);
    this->procMat();
    this->getEyes();
    this->procEyes();
    if(this->goodFrame)
        this->finishMat();
}

void FacePre::finishMat(){
    this->geometricTransformation();
    this->histogram();
    this->smoothing();
    this->ellipseMask();
}

void FacePre::smoothing(){
    Mat filtered = Mat(this->frame.size(), CV_8U);
    bilateralFilter(this->frame, filtered, 0, 20.0, 2.0);
    filtered.copyTo(this->frame);
}

void FacePre::ellipseMask(){
    Mat mask = Mat(this->frame.size(), CV_8UC1, Scalar(255));
    Point faceCenter = Point( cvRound(DESIRED_FACE_WIDTH * 0.5), cvRound(DESIRED_FACE_HEIGHT * 0.4) );
    Size size = Size( cvRound(DESIRED_FACE_WIDTH * 0.5), cvRound(DESIRED_FACE_HEIGHT * 0.8) );
    ellipse(mask, faceCenter, size, 0, 0, 360, Scalar(0), CV_FILLED);
    this->frame.setTo(Scalar(128), mask);
}

void FacePre::histogram(){
    int w = this->frame.cols;
    int h = this->frame.rows;
    Mat wholeFace;
    equalizeHist(this->frame, wholeFace);

    int midX = w/2;
    Mat leftSide = this->frame(Rect(0,0, midX, h));
    Mat rightSide = this->frame(Rect(midX,0,w-midX,h));
    equalizeHist(leftSide, leftSide);
    equalizeHist(rightSide, rightSide);

    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            int v;
            if (x < w/4) {
                // Left 25%: just use the left face.
                v = leftSide.at<uchar>(y,x);
            }
            else if (x < w*2/4) {
                // Mid-left 25%: blend the left face & whole face.
                int lv = leftSide.at<uchar>(y,x);
                int wv = wholeFace.at<uchar>(y,x);
                // Blend more of the whole face as it moves
                // further right along the face.
                float f = (x - w*1/4) / (float)(w/4);
                v = cvRound((1.0f - f) * lv + (f) * wv);
            }
            else if (x < w*3/4) {
                // Mid-right 25%: blend right face & whole face.
                int rv = rightSide.at<uchar>(y,x-midX);
                int wv = wholeFace.at<uchar>(y,x);
                // Blend more of the right-side face as it moves
                // further right along the face.
                float f = (x - w*2/4) / (float)(w/4);
                v = cvRound((1.0f - f) * wv + (f) * rv);
            }
            else {
                // Right 25%: just use the right face.
                v = rightSide.at<uchar>(y,x-midX);
            }
            this->frame.at<uchar>(y,x) = v;
        }// end x loop
    }//end y loop
}

void FacePre::geometricTransformation(){
    //Transformação geométrica
    Point eyesCenter;
    eyesCenter.x = (this->leftEye.x + this->rightEye.x) * 0.5f;
    eyesCenter.y = (this->leftEye.y + this->rightEye.y) * 0.5f;

    double dx = (this->rightEye.x - this->leftEye.x);
    double dy = (this->rightEye.y - this->leftEye.y);
    double len = sqrt(dx*dx + dy*dy);
    double angle = atan2(dy, dx) * 180.0/CV_PI;

    double desiredLen = (DESIRED_RIGHT_EYE_X - 0.16);
    double scale = desiredLen * DESIRED_FACE_WIDTH / len;

    Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, scale);
    double ex = DESIRED_FACE_WIDTH * 0.5f - eyesCenter.x;
    double ey = DESIRED_FACE_HEIGHT * 0.14 - eyesCenter.y;
    rot_mat.at<double>(0, 2) += ex;
    rot_mat.at<double>(1, 2) += ey;
    Mat warped = Mat(DESIRED_FACE_HEIGHT, DESIRED_FACE_WIDTH, CV_8U, Scalar(128));
    warpAffine(this->frame, warped, rot_mat, warped.size());
    warped.copyTo(this->frame);
}

void FacePre::getEyes(){
    int leftX = cvRound(this->frame.cols * EYE_SX);
    int topY = cvRound(this->frame.rows * EYE_SY);
    int widthX = cvRound(this->frame.cols * EYE_SW);
    int heightY = cvRound(this->frame.rows * EYE_SH);
    int rightX = cvRound(this->frame.cols * (1.0-EYE_SX-EYE_SW));

    this->topLeft = this->frame(Rect(leftX, topY, widthX, heightY));
    this->topRight = this->frame(Rect(rightX, topY, widthX, heightY));
}

void FacePre::procEyes(){
    cout << "Finding eyes..." << endl;
    int leftX = cvRound(this->frame.cols * EYE_SX);
    int topY = cvRound(this->frame.rows * EYE_SY);
    int rightX = cvRound(this->frame.cols * (1.0-EYE_SX-EYE_SW));

    bool leftEyeFound=false, rightEyeFound=false;
    std::vector<Rect> eyeRect;
    this->eyeDetector.detectMultiScale(this->topLeft, eyeRect, 1.1, 5, CASCADE_FIND_BIGGEST_OBJECT, Size(20, 20));
    if(eyeRect.size() > 0)
        rightEyeFound = true;
    else{
        this->eyeDetector2.detectMultiScale(this->topLeft, eyeRect, 1.1, 5, CASCADE_FIND_BIGGEST_OBJECT, Size(20, 20));
        if(eyeRect.size() > 0)
            rightEyeFound = true;
    }
    if(rightEyeFound)
        this->leftEye = Point(eyeRect[0].x + eyeRect[0].width/2 + leftX, eyeRect[0].y + eyeRect[0].height/2 + topY);

    eyeRect.clear();
    this->eyeDetector.detectMultiScale(this->topRight, eyeRect, 1.1, 5, CASCADE_FIND_BIGGEST_OBJECT, Size(20, 20));
    if(eyeRect.size() > 0)
        leftEyeFound = true;
    else{
        this->eyeDetector2.detectMultiScale(this->topRight, eyeRect, 1.1, 5, CASCADE_FIND_BIGGEST_OBJECT, Size(20, 20));
        if(eyeRect.size() > 0)
            leftEyeFound = true;
    }
    if(leftEyeFound)
        this->rightEye = Point(eyeRect[0].x + eyeRect[0].width/2 + rightX, eyeRect[0].y + eyeRect[0].height/2 + topY);

    if(leftEyeFound && rightEyeFound){
        cout << "Found!" << endl;
        this->goodFrame = true;
      }
    else{
      cout << "Not found!" << endl;
    }
}

void FacePre::procMat(){
    cvtColor(this->frame, this->frame, CV_BGR2GRAY);
    equalizeHist(this->frame, this->frame);
}

Mat FacePre::getFrame(){
    return this->frame;
}

bool FacePre::isGoodFrame(){
    return this->goodFrame;
}
