#include "trainer.hpp"
#include <opencv2/face.hpp>
#include <opencv2/core.hpp>
#define UNKNOWN_PERSON_THRESHOLD 0.7

using namespace cv;
Trainer::Trainer(unsigned short int mode){
    this->trainerMode = mode;
    if(mode == TRAINER_FISHERFACE)
        this->model = createFisherFaceRecognizer();
    if(mode == TRAINER_EIGENFACE)
        this->model = createEigenFaceRecognizer();
}

void Trainer::save(string path, string name){
    this->model->save(path+name);
}


void Trainer::train(string path, vector<string> name, int quantity){
    vector<Mat> images;
    vector<int> labels;

    for(unsigned int i = 0; i < name.size(); i++){
        for(int j=0; j<quantity; j++){
            ostringstream convert;
            convert << j;
            images.push_back(imread(path+name[i] + "/frame" + convert.str() + ".jpg", CV_LOAD_IMAGE_GRAYSCALE));
            cout << path+name[i] + "/frame" + convert.str() + ".jpg" << endl;
            labels.push_back(atoi(name.at(i).c_str()));
        }
    }
    this->model->train(images, labels);
}
