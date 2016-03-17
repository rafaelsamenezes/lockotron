#include <iostream>
#include "trainer.hpp"
#include <opencv2/core.hpp>
using namespace std;


void testRecognition(){

    Trainer t(TRAINER_FISHERFACE);
    string path = "/home/rafael/Testes/";
    /*
    vector<string> ids;
    ids.push_back("1");
    ids.push_back("2");
    ids.push_back("3");
    ids.push_back("4");
    ids.push_back("5");
    ids.push_back("6");

    t.train(path, ids, 30);
    */
    t.save("/home/rafael/", "faces.xml");
}


int main()
{
    testRecognition();
    return 0;
}
