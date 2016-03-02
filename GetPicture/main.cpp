#include "picture.h"

int main(int argc, char *argv[])
{
    if(argc < 1 || argc > 2)
        cerr << "ERROR: Usage ./GetPicture <path>" << endl;

    Picture p(0);
    p.begin(argv[1]);

}

