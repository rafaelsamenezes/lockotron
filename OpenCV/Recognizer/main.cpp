#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/contrib/contrib.hpp>
#define UNKNOWN_PERSON_THRESHOLD 0.7
#define faceHeight 0.5
using namespace std;
using namespace cv;

int isGoodRecognition();
double getSimilarity(const Mat A, const Mat B);

string fisherface = "FaceRecognize.Fisherfaces";
string eigenface = "FaceRecognize.Eigenfaces";
string lbph = "FaceRecognize.LBPH";
Ptr<FaceRecognizer> model;
Mat preprocessedFace;


int main(int argc, char* argv[])
{
  model = Algorithm::create<FaceRecognizer>(fisherface);
  model->load(argv[1]);
  preprocessedFace = imread(argv[2]);
  return 0;
}

int isGoodRecognition(){
  Mat eigenvectors = model->get<Mat>("eigenvectors");
  Mat averageFaceRow = model->get<Mat>("mean");
  // Project the input image onto the eigenspace.
  Mat projection = subspaceProject(eigenvectors, averageFaceRow, preprocessedFace.reshape(1,1));
    // Generate the reconstructed face back from the eigenspace.
  Mat reconstructionRow = subspaceReconstruct(eigenvectors, averageFaceRow, projection);
  Mat reconstructionMat = reconstructionRow.reshape(1, faceHeight);
    // Convert the floating-point pixels to regular 8-bit uchar.
  Mat reconstructedFace = Mat(reconstructionMat.size(), CV_8U);
  reconstructionMat.convertTo(reconstructedFace, CV_8U, 1, 0);
  double similarity = getSimilarity(preprocessedFace,  reconstructedFace);
  if (similarity > UNKNOWN_PERSON_THRESHOLD) {
    return 0;
  // Unknown person.
  }
  return 1;
}

double getSimilarity(const Mat A, const Mat B) {
  // Calculate the L2 relative error between the 2 images.
  double errorL2 = norm(A, B, CV_L2);
  // Scale the value since L2 is summed across all pixels.
  double similarity = errorL2 / (double)(A.rows * A.cols);
  return similarity;
}
