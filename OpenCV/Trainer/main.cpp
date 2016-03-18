#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/contrib/contrib.hpp>
using namespace std;
using namespace cv;

string fisherface = "FaceRecognize.Fisherfaces";
string eigenface = "FaceRecognize.Eigenfaces";
string lbph = "FaceRecognize.LBPH";

std::vector<Mat> frames;
std::vector<int> labels;

int main()
{
  Ptr<FaceRecognizer> model;
  model = Algorithm::create<FaceRecognizer>(fisherface);
  //model->train(frames, labels);
  //model->save("faces.xml");

}
