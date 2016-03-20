#include "facedetection.h"
#include <opencv2/core.hpp>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]){
    if (argc == 0)
      cerr << "Usage ./" << argv[0] << " <save_folder>" << endl;
    FaceDetection fd(1, argv[1]);
    fd.readWebCam();

}
