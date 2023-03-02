#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include <iostream>
#include "Tweet.h"
#include <vector>

using namespace std;

class SentimentClassifier
{
    private:
        
    public: 
        void train(vector<Tweet>); //Read in training data and indentify words with certain sentiments.
        void predict(); //Read in a dataset and assign 
        void analyze(); //Check accuracy

};

#endif