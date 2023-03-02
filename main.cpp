#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "DSString.h"
#include <string>

using namespace std;

int main(int argc, char** argv)
{  
    char filename[] = "./data/test_dataset_sentiment_10k.csv";
    FILE *stream;

    vector<DSString> storage;

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
        //cout << "I read " << nread << " character: " << buffer;
        DSString newdata = buffer;
        storage.push_back(newdata);
    }
    

    for(int x=0; x<storage.size(); x++)
    {
        cout << storage.at(x);
    }


    Tweet testtweet = storage.at(1).convertToTweet();

    cout << "GetID test: " << testtweet.getID() << endl;

    fclose(stream);


    return(0);
}