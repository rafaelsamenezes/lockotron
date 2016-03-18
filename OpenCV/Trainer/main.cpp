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
void loadFrames();

int main(int argc, char* argv[])
{
  string path = argv[1];
  Ptr<FaceRecognizer> model;
  model = Algorithm::create<FaceRecognizer>(fisherface);
  loadFrames();
  //model->train(frames, labels);
  //

  vector<Mat> images;
  vector<int> labels;

  for(unsigned int i = 0; i < names.size(); i++){
      for(int j=0; j<quantity; j++){
          ostringstream convert;
          convert << j;
          images.push_back(imread(path+names[i] + "/frame" + convert.str() + ".jpg", CV_LOAD_IMAGE_GRAYSCALE));
          cout << path+names[i] + "/frame" + convert.str() + ".jpg" << endl;
          labels.push_back(atoi(names.at(i).c_str()));
      }
  }
  model->train(images, labels);
  model->save("faces.xml");
}

void loadFrames(){
  quantity = 60;
  names.push_back("0");
  names.push_back("1");
}
