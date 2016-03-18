#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/contrib/contrib.hpp>
using namespace std;
using namespace cv;

int main(){
  std::vector<int> v;
  vector<string> algorithms;
  Algorithm::getList(algorithms);
  cout << "Algorithms: " << algorithms.size() << endl;
  for (int i=0; i<algorithms.size(); i++) {
    cout << algorithms[i] << endl;
  }

  // Load the "contrib" module is dynamically at runtime.
  bool haveContribModule = initModule_contrib();
  if (!haveContribModule) {
    cerr << "ERROR: The 'contrib' module is needed for ";
    cerr << "FaceRecognizer but hasn't been loaded to OpenCV!";
    cerr << endl;
    exit(1);


  }
  cout << "You are good to go *-*" << endl;
}
