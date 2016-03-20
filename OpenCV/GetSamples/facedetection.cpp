#include "facedetection.h"
#include <iostream>
#include "haarcascade.h"
#include <time.h>

using namespace std;

FaceDetection::FaceDetection(int camera, string path){
    if(!this->faceCascade.load( HaarCascade::faceHaarCascade ) ){
       cerr << "ERROR: Face Cascade " << HaarCascade::faceHaarCascade << " couldn't be loaded!" << endl;
       exit(-1);
    }
    this->save_path = path;

    this->savedFrames = 0;
    this->webCam = VideoCapture(camera);
}

void FaceDetection::detectAndDisplay(){
    Mat frame_gray;
    this->frame.copyTo(this->detectedFrame);
    cvtColor( this->frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    this->faceCascade.detectMultiScale( frame_gray, this->faces, 1.1, 5, CASCADE_FIND_BIGGEST_OBJECT, Size(120, 120) );
    //cout << "Faces found: " << this->faces.size();
    if (this->faces.size() > 0)
        rectangle(this->detectedFrame, faces[0], Scalar( 0, 0, 255 ), 3);
    imshow("Detecção de Rostos", this->detectedFrame);
    //this->old_frame.copyTo(this->detectedFrame);
    cvtColor( this->old_frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    this->faceCascade.detectMultiScale( frame_gray, this->old_faces, 1.1, 5, CASCADE_FIND_BIGGEST_OBJECT, Size(120, 120) );

}

void FaceDetection::saveFrame(FacePre face){
    ostringstream convert;
    convert << this->savedFrames;
    if(face.isGoodFrame()){
        imwrite(this->save_path + "frame" + convert.str() + ".jpg", face.getFrame());
        this->savedFrames++;

          cout << this->savedFrames << endl;
        ostringstream convert2;
        convert2 << this->savedFrames;
        Mat fliped_face;
        cv::flip(face.getFrame(), fliped_face, 1);
        imwrite(this->save_path + "frame" + convert2.str() + ".jpg", fliped_face);
        this->savedFrames++;
        cout << this->savedFrames << endl;
    }
}

double FaceDetection::getSimilarity(const Mat A, const Mat B) {
  if (A.size != B.size){
    this->frame.copyTo(this->old_frame);
    return 0;

  }

  // Calculate the L2 relative error between the 2 images.
  double errorL2 = norm(A, B, CV_L2);
  // Scale the value since L2 is summed across all pixels.
  double similarity = errorL2 / (double)(A.rows * A.cols);
  return similarity;
}

void FaceDetection::readWebCam(){
  this->webCam >> this->old_frame;
  clock_t old_time = clock();

  while(1){
    clock_t current_time = clock();
    this->webCam >> this->frame;
    this->detectAndDisplay();
    if(this->old_faces.size() == 0){
      this->frame.copyTo(this->old_frame);
    }
    else if (this->old_frame.size != this->frame.size){
      this->frame.copyTo(this->old_frame);
    }
    else if (this->faces.size() > 0 && difftime(current_time, old_time) > 1){
      Mat croped_old_face = this->old_frame(this->old_faces[0]);
      FacePre old_face(croped_old_face);
      Mat croped_face = this->frame(this->faces[0]);
      FacePre new_face(croped_face);
      double similarity = this->getSimilarity(new_face.getFrame(), old_face.getFrame());
      if (similarity > 0.3){
        if (new_face.isGoodFrame()){
          old_time = clock();

          this->frame.copyTo(this->old_frame);
          this->saveFrame(new_face);
        }
      }
    }

    if (waitKey(20) == 27)
      break;
  }

}
