#include <iostream>
#include "recognizer.hpp"
#include <opencv2/core.hpp>
using namespace std;


int main(int argc, char* argv[])
{
    Recognizer r(argv[1], argv[2]);
    cout << r.recognize();
    return 0;
}
