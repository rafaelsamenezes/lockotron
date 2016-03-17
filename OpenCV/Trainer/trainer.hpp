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
class Trainer
{
private:
    unsigned short int trainerMode;
    Ptr<BasicFaceRecognizer> model;

public:
    Trainer(unsigned short int mode);
    void saveTrainer(string path, string name);
    void train(string path, vector<string> name, int quantity);
    void save(string path, string name);

};

#endif
