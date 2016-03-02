#ifndef TRAINER_H
#define TRAINER_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/face.hpp>
#include "facepre.h"

#define TRAINER_FISHERFACE 0
#define TRAINER_EIGENFACE 1


using namespace cv;
using namespace face;
using namespace std;
class Trainer
{
private:
    unsigned short int trainerMode;
    Ptr<BasicFaceRecognizer> model;
    vector<string> names;
    int numberModels;
    FacePre fp;
    bool isGoodRecognition(Mat frame, int p);
    string getName(int p);
public:
    Trainer(unsigned short int mode);
    //~Trainer() { model.release();}
    int recognize(Mat frame);
    void saveTrainer(string path, string name);
    void train(string path, vector<string> name, int quantity);
    void save(string path, string name);
    void load(string path, string name);
    void readWebcam();

};

#endif
