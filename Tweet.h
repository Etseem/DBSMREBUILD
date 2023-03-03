#ifndef TWEET_H
#define TWEET_H

#include <iostream>
#include <vector>

//This class exists to make DSString not so cluttered.

using namespace std;

class Tweet
{
    private:
        int id; //Tweet ID
        int sentiment; //For training data, the ACTUAL sentiment value.
        int predictedSentiment; //For assigning what the program thinks this tweet's sentiment is.
        
    public: 
        Tweet();
        void Initialize();
        int getID();
        int getSentiment();
        int getPredicted();
        void setID(int);
        void setSentiment(int);
        void setPredicted(int);
        vector<int> wordvec;
        vector<char> garbvec; // Holds all commas and stuff.

};

#endif