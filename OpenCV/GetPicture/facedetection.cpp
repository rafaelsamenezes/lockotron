#include "facedetection.h"
#include <iostream>
#include "haarcascade.h"

using namespace std;

FaceDetection::FaceDetection(){
    FaceDetection(0);
}

FaceDetection::FaceDetection(Mat frame){
    if(!this->faceCascade.load( HaarCascade::faceHaarCascade ) ){
       cerr << "ERROR: Face Cascade " << HaarCascade::faceHaarCascade << " couldn't be loaded!" << endl;
       exit(-1);
    }

    this->frame = frame;
    this->detectAndDisplay();
}

Mat FaceDetection::getDetectedFrame(){
    return this->detectedFrame;
}

FaceDetection::FaceDetection(int camera){
    if(!this->faceCascade.load( HaarCascade::faceHaarCascade ) ){
       cerr << "ERROR: Face Cascade " << HaarCascade::faceHaarCascade << " couldn't be loaded!" << endl;
       exit(-1);
    }

    this->savedFrames = 0;
    this->webCam = VideoCapture(camera);
}


void FaceDetection::detectAndDisplay(){
    Mat frame_gray;
    this->frame.copyTo(this->detectedFrame);
    cvtColor( this->frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    this->faceCascade.detectMultiScale( frame_gray, this->faces, 1.1, 5, CASCADE_FIND_BIGGEST_OBJECT, Size(120, 120) );

    for( size_t i = 0; i < this->faces.size(); i++ ){
        rectangle(this->detectedFrame, faces[i], Scalar( 0, 0, 255 ), 3);
    }
}

void FaceDetection::saveFrame(){
    ostringstream convert;
    convert << this->savedFrames;
    Mat cropedFrame = this->frame(this->faces[0]);
    FacePre face(cropedFrame);
    if(face.isGoodFrame()){
        imwrite("/home/rafael/Testes/frame" + convert.str() + ".jpg", face.getFrame());
        this->savedFrames++;
        cout << this->savedFrames << endl;
    }
}

void FaceDetection::readVideoFile(String video_file){
    VideoCapture video(video_file);

    if (!video.isOpened())
        cerr << "ERROR: Could not open: " << video_file;

    while (1) {
        //video.
        video >> this->frame;

        if(this->frame.empty()){

            break;

        }
        this->detectAndDisplay();

        imshow("Face Detection Video", this->detectedFrame);
        int keyPressed = waitKey(10);
        if(keyPressed == 27)
            break;
            this->saveFrame();

    }

}


void FaceDetection::readWebCam(){
    while(1){
        this->webCam >> this->frame;
        if(this->frame.empty()){
            cerr << "ERROR: Problem with default camera" << endl;
            exit(-1);
        }
        this->detectAndDisplay();
        imshow("Test Face Detection", this->detectedFrame);
        int keyPressed = waitKey(100);
        if(keyPressed == 27)
            break;
        this->saveFrame();

        //waitKey(100);
    }

}
