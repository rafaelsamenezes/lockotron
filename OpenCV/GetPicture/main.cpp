#include "picture.h"

int main(int argc, char *argv[])
{
    if(argc < 2 || argc > 3)
        cerr << "ERROR: Usage ./GetPicture <path>" << endl;

    Picture p(0);
    p.begin(argv[1]);

}
