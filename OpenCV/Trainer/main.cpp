#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/contrib/contrib.hpp>
using namespace std;
using namespace cv;

string fisherface = "FaceRecognizer.Fisherfaces";
string eigenface = "FaceRecognizer.Eigenfaces";
string lbph = "FaceRecognizer.LBPH";

//std::vector<Mat> frames;
std::vector<string> names;
int quantity;
void loadFrames(int samples);

int main(int argc, char* argv[])
{
  if (argc < 2)
    cerr << "Usage: ./Trainer <path-to-samples> <path-to-target> <samples-number> <ids>" << endl;
  string path_samples = argv[1];
  string path_target = argv[2];
  quantity = atoi(argv[3]);
  loadFrames(atoi(argv[4]));

  Ptr<FaceRecognizer> model;
  model = Algorithm::create<FaceRecognizer>(fisherface);
  //model->train(frames, labels);
  //

  vector<Mat> images;
  vector<int> labels;

  for(unsigned int i = 0; i < names.size(); i++){
      for(int j=0; j<quantity; j++){
          ostringstream convert;
          convert << j;
          images.push_back(imread(path_samples+names[i] + "/frame" + convert.str() + ".jpg", CV_LOAD_IMAGE_GRAYSCALE));
          cout << path_samples+names[i] + "/frame" + convert.str() + ".jpg" << endl;
          labels.push_back(atoi(names.at(i).c_str()));
      }
  }
  model->train(images, labels);
  model->save(path_target + "faces.xml");
}

void loadFrames(int samples){
  int i = 1;
  //quantity = quantity;
  for(;i<=samples; i++){
    ostringstream convert;
    convert << i;
    names.push_back(convert.str());
  }
}
