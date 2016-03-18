#include "picture.h"
#include <unistd.h>
#include "facepre.h"
#include "facedetection.h"
Picture::Picture()
{
    Picture(0);
}

Picture::Picture(int camera)
{
    this->cv = VideoCapture(camera);

    if(!this->cv.isOpened())
        cerr << "ERROR: Failed to open camera " << camera << endl;
}

void Picture::begin(string path){
    while(1){
        Mat frame;
        this->cv >> frame;

        if(!frame.isContinuous()){
            cerr << "ERROR: Failed to get frame from camera" << endl;
        }
        FaceDetection fd(frame);
        fd.detectAndDisplay();
        if (fd.faces.size() > 0){
        Mat cropedFrame = frame(fd.faces[0]);
        FacePre fp(cropedFrame);
        if(fp.isGoodFrame()){
            if(!imwrite(path + "frame.jpg", fp.getFrame()))
                cerr << "ERROR: Failed to save frame: " << path << "frame.jpg" << endl;
            else
                cout << "Saved: " << path << "frame.jpg" << endl;
            usleep(500000);
        }
      }
      else
        cout << "Face not found in frame!" << endl;

    }


}
