#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "DSString.h"
#include "Tweet.h"
#include "SentimentClassifier.h"
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) 
//Tested using the command line arguments: ./classifier.out data/train_dataset_20k.csv data/test_dataset_10k.csv data/test_dataset_sentiment_10k.csv results.csv accuracy.txt
//Built using the command 'g++ *.cpp *.h -o DBSMREBUILD
//Run using the command ./DBSMREBUILD [command line arguments here]
{  
    
    vector<DSString*> storage2; //Stores training dataset

    vector<DSString> storage1; //Stores test dataset results, just ID and sentiment associated.
    vector<Tweet> storage1convert; //Stores values from storage1 that have been converted to tweets. (Broken up)

    vector<DSString*> storage; //Stores non sentiment test dataset

    fstream fout;

    //Read in training dataset

    cout << "Opening: " << argv[2] << endl;

    fout.open(argv[2], ios::in);
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

        //Since Date, Query, and User are not useful information, they aren't used again.

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

        newdsstring->convertToWords(); //Convert the tweets into individual words

        storage2.push_back(newdsstring); //Add it to storage.

    }while(fout.good());

    
    fout.close();



    //Read in sentiment test dataset
    char filename[256]; //Uses C File I/O from the example
    strcpy(filename, argv[4]); //Copy argv2 to filename.
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
        storage1convert.push_back(testweet);
    }
    

           fclose(stream);

   //Read non-sentiment test dataset

    string testdataset = argv[3];

    fout.open(testdataset, ios::in);

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
        DSString* newdsstring = new DSString(inp);
        newdsstring->addID(foo);
        newdsstring->convertToWords();
        storage.push_back(newdsstring);

    }while(fout.good());


    //Storage.at(0) is the first line, so it does not follow the same rules as the other ones. Do not call it.


    //Now that we have all the data good to go we can use the sentiment classifier.
    SentimentClassifier jeff; //I figured it'd be fun to pretend that this class was a person named Jeff.
    cout << "Beginning Training!" << endl;
    jeff.train(storage2); //Train on the dataset.
    cout << "Done Training!" << endl;
    jeff.predict(storage); //Pass in data to predict.
    cout << "Done Predicting!" << endl;
    float accuracy = jeff.analyze(storage1convert, storage); //Determine accuracy.
    cout << "Done Analyzing!" << endl;


    ofstream predictions; //Outputs the predictions to a .csv file.
    predictions.open(argv[5]);

    for(int x=1; x<storage.size()-1; x++)
    {
        predictions << storage.at(x)->predictedSentiment << "," << storage.at(x)->id << "\n";
    }

    predictions.close();

    ofstream outputAccuracy; //Outputs the results, with the prediction, the actual answer, then the ID.
    outputAccuracy.open(argv[6]);

    outputAccuracy << fixed << setprecision(3) << accuracy << "\n"; //Write the first line (Accuracy to 3 decimal points)
    for(int x=1; x<storage.size()-1; x++)
    {
        outputAccuracy << storage.at(x)->predictedSentiment << "," << storage1convert.at(x).getSentiment() << "," << storage.at(x)->id << "\n";
    }

    outputAccuracy.close();
    

   //Clean up
   storage.clear();
   storage1.clear();
   storage2.clear();
   storage1convert.clear();
   fout.close();
   
   
    return(0);
}