#include <iostream>
#include <trainer.h>
#include <opencv2/core.hpp>
#include <facepre.h>
using namespace std;


void testRecognition(){

    Trainer t(TRAINER_FISHERFACE);
    string path = "/home/rafael/Testes/";

    vector<string> ids;
    ids.push_back("1");
    ids.push_back("2");
    /*ids.push_back("3");
    ids.push_back("4");
    ids.push_back("5");
    ids.push_back("6");
    */
    t.train(path, ids, 30);
    t.saveTrainer("/home/rafael/Testes/", "faces.xml");

    t.readWebcam();
    /*cv::Mat frame = imread("face1.pgm");
    FacePre f(frame);
    cout << f.isGoodFrame();*/
    //t.recognize(f.getFrame());
}




int main()
{
    testRecognition();
    return 0;
}

