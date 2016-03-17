#include "trainer.h"
#include "facedetection.h"
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
    /*else
        this->model = createLBPHFaceRecognizer();
        */
}

void Trainer::saveTrainer(string path, string name){
    this->model->save(path+name);
}


string Trainer::getName(int p){
    return this->names[p];
}

void Trainer::train(string path, vector<string> name, int quantity){
    vector<Mat> images;
    vector<int> labels;
    this->numberModels = name.size();

    for(unsigned int i = 0; i < name.size(); i++){
        this->names.push_back(name[i]);
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


double Trainer::getSimilarity(Mat A, Mat B){
        // Calculate the L2 relative error between images.
        double errorL2 = norm( A, B, CV_L2 );
        // Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
        double similarity = errorL2 / (double)( A.rows * A.cols );
        return similarity;

}

bool Trainer::isGoodRecognition(Mat f, int p){


    Mat W = this->model->getEigenVectors();

    Mat mean = this->model->getMean();
    Mat frame;
    f.copyTo(frame);

    // Project the input image onto the eigenspace.


    Mat projection = LDA::subspaceProject(W, mean, frame.reshape(1,1));
    Mat reconstructionRow = LDA::subspaceReconstruct(W, mean, projection);

    Mat reconstructionMat = reconstructionRow.reshape(1, 70);

    Mat reconstructedFace = Mat(reconstructionMat.size(), CV_8U);
    reconstructionMat.convertTo(reconstructedFace, CV_8U, 1, 0);

    imshow("Projetion", reconstructedFace);
    waitKey(0);
    double similarity = getSimilarity(f, reconstructedFace);

    cout << "Similaridade: " << similarity << endl;

    if (similarity < UNKNOWN_PERSON_THRESHOLD) {
        return false;
    // Unknown person.
    }

    return true;

}



void Trainer::load(string path, string name){
    this->model->load(path+name);
}


int Trainer::recognize(Mat frame){
    int predicted;
    double confidence;
    //this->model->predict()
    this->model->predict(frame, predicted, confidence);
    cout << "Certeza: " << confidence << endl;

    if (this->isGoodRecognition(frame,0)){
        return predicted;
    }

    return -1;
}

void Trainer::readWebcam(){
    VideoCapture web(0);
    if(!web.isOpened())
        cerr << "ERROR: trainer, Could not open camera";
    while(1){
        Mat frame, frame2;
        web >> frame;
        frame.copyTo(frame2);
        FaceDetection face(frame2);
        imshow("Deteccao", face.getDetectedFrame());
        this->fp = FacePre(frame);

        if(this->fp.isGoodFrame()){
            imshow("teste", this->fp.getFrame());
            int confidence = this->recognize(this->fp.getFrame());

            if(confidence >= 0){
                //cout << "Olá " << this->getName(confidence) << endl;
                cout << "Olá " << confidence << endl;

            }
            else
                cout << "Não foi identificado" << endl;
        }

        if(waitKey(10) == 27)
            break;
    }
}
