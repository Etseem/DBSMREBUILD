#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "DSString.h"
//#include <string>

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
        DSString newdata = buffer;
        storage.push_back(newdata);
    }
    

    for(int x=0; x<storage.size(); x++)
    {
        cout << storage.at(x);
    }


    Tweet testtweet = storage.at(1).convertToTweet();

    cout << "Get Sentiment test: " << testtweet.getSentiment() << endl;
    cout << "Printing ID: " << testtweet.getID() << endl;
    cout << endl;

    Tweet testtweet2 = storage.at(2).convertToTweet();
    cout << "Get Sentiment test: " << testtweet2.getSentiment() << endl;
    cout << "Printing ID: " << testtweet2.getID() << endl;
    cout << endl;

    storage.clear();

    fclose(stream);


    return(0);
}