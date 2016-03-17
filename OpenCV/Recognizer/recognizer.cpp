#include "recognizer.hpp"

#define UNKNOWN_PERSON_THRESHOLD 0.7

using namespace cv;

Recognizer::Recognizer(string path_frame, string path_xml){
  this->load(path_xml);
  this->frame = imread(path_frame);
}

void Recognizer::load(string path_xml){
  this->model->load(path_xml);
}

double Recognizer::getSimilarity(Mat A, Mat B){
        // Calculate the L2 relative error between images.
        double errorL2 = norm( A, B, CV_L2 );
        // Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
        double similarity = errorL2 / (double)( A.rows * A.cols );
        return similarity;

}

bool Recognizer::isGoodRecognition(Mat f, int p){


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

    double similarity = getSimilarity(f, reconstructedFace);

    cout << "Similaridade: " << similarity << endl;

    if (similarity < UNKNOWN_PERSON_THRESHOLD) {
        return false;
    // Unknown person.
    }

    return true;

}




int Recognizer::recognize(){
    int predicted;
    double confidence;
    //this->model->predict()
    this->model->predict(this->frame, predicted, confidence);
    cout << "Certeza: " << confidence << endl;

    if (this->isGoodRecognition(this->frame,0)){
        return predicted;
    }

    return -1;
}
