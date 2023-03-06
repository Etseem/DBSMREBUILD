#ifndef TWEET_H
#define TWEET_H

#include <iostream>
#include <vector>

//This class exists to make DSString not so cluttered.

using namespace std;

class Tweet
{
    private:
        long id; //Tweet ID
        int sentiment; //For training data, the ACTUAL sentiment value.
        int predictedSentiment; //For assigning what the program thinks this tweet's sentiment is.
        
    public: 
        Tweet();
        void Initialize();
        long getID();
        int getSentiment();
        int getPredicted();
        void setID(long);
        void setSentiment(int);
        void setPredicted(int);
};

#endif