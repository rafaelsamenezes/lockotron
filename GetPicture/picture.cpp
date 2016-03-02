#include "picture.h"
#include <unistd.h>
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
    Timer t;
    while(1){
        Mat frame;
        this->cv >> frame;

        if(!frame.isContinuous()){
            cerr << "ERROR: Failed to get frame from camera" << endl;
        }
        if(!imwrite(path + "frame.jpg", frame))
                cerr << "ERROR: Failed to save frame: " << path << "frame.jpg" << endl;
        else
            cout << "Saved: " << path << "frame.jpg" << endl;

       usleep(1000000);

    }


}
