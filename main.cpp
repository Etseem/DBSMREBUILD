#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "DSString.h"

using namespace std;

int main(int argc, char** argv)
{  
    char filename[] = "./data/test_dataset_sentiment_10k.csv";
    FILE *stream;

    char buffer[1001];
    char *b = buffer;
    size_t maxlen = 1000;

    size_t nread;

    stream = fopen(filename, "r");
    if(stream == NULL)
    {
        cerr << "Opening the file failed!" << endl;
        return(-1);
    }

    while ((nread = getline(&b, &maxlen, stream)) != -1)
    {
        cout << "I read " << nread << " character: " << buffer;
    }

    cout << endl;

    fclose(stream);

    cout << "Debug Message" << endl;

    return(0);
}