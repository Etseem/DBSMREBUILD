#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "DSString.h"
#include "Tweet.h"
#include "SentimentClassifier.h"
//#include <string>

using namespace std;

int main(int argc, char** argv)
{  
    
    vector<DSString*> storage2; //Stores training dataset

    vector<DSString> storage1; //Stores test dataset results, just ID and sentiment associated.
    vector<Tweet> storage1convert; //Stores values from storage1 that have been converted to tweets. (Broken up)

    vector<DSString> storage; //Stores non sentiment test dataset


    fstream fout;

    //Read in training dataset
    fout.open("train_dataset_20k.csv", ios::in);
    if(fout.fail())
    {
        cerr << "Opening the file failed!" << endl;
        return -1;
    }
    string foo, foo1, foo2, foo3, foo4, foo5; //Dummy strings for getline
    do
    {
        getline(fout, foo5, ','); //Read in sentiment
        getline(fout, foo, ','); //Read in ID
        getline(fout, foo1, ','); //Read in Date
        getline(fout, foo2, ','); //Read in Query
        getline(fout, foo3, ','); //Read in User
        getline(fout, foo4); //Read until the end of the line.

        const char *inp = foo4.c_str();
        DSString* newdsstring = new DSString(inp);
        newdsstring->addID(foo);
        char chararray[1]; 
        strcpy(chararray, foo5.c_str());

        if(chararray[0] == '0')
        {
            newdsstring->sentiment = 0;

        }
        else if(chararray[0] == '4')
        {
            newdsstring->sentiment = 4;
        }

        storage2.push_back(newdsstring);
        //cout << "Pushed back a DSString with an ID of: " << newdsstring.id << " and a sentiment of " << newdsstring.sentiment << endl;

    }while(fout.good());

    
    fout.close();


    //Read in sentiment test dataset
    char filename[] = "test_dataset_sentiment_10k.csv";
    FILE *stream;
    char buffer[1001];
    size_t maxlen = 1000;

    size_t nread;

    stream = fopen(filename, "r");

    if(stream == NULL)
    {
        cerr << "Opening the file failed!" << endl;
        return(-1);
    }

    while (fgets(buffer, sizeof(buffer), stream) != NULL) //Read in valuies
    {
        DSString newdata = buffer;
        storage1.push_back(newdata);
    }
    
    for(int x = 0; x<storage1.size(); x++)
    {
        Tweet testweet = storage1.at(x).convertToTweet(); //Use convertToTweet function to break into ID and Sentiment
        //cout << testweet.getID() << endl;
        storage1convert.push_back(testweet);
        //cout << storage1convert.at(x).getID() << endl;
    }
    

           fclose(stream);

   //Read non sentiment test dataset

    fout.open("test_dataset_10k.csv", ios::in);

    if(fout.fail())
    {
        cerr << "Opening the file failed!" << endl;
        return -1;
    }

    do
    {
        getline(fout, foo, ','); //Read in ID
        getline(fout, foo1, ','); //Read in Date
        getline(fout, foo2, ','); //Read in Query
        getline(fout, foo3, ','); //Read in User
        getline(fout, foo4); //Read until the end of the line.

        const char *inp = foo4.c_str();
        DSString newdsstring(inp);
        newdsstring.addID(foo);

        storage.push_back(newdsstring);

    }while(fout.good());

    //Storage.at(0) is the first line. Do not call under any circumstances :]

    

    //Now that we have all the data good to go we can use the sentiment classifier.
    SentimentClassifier jeff;

    

    jeff.train(storage2);
    //jeff.predict(storage);
    //jeff.analyze(storage1convert);

   //Clean up
   storage.clear();
   storage1.clear();
   storage2.clear();
   storage1convert.clear();
   fout.close();
   
    return(0);
}