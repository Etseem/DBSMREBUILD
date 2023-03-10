#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include <iostream>
#include "Tweet.h"
#include "DSString.h"
#include <vector>

using namespace std;

class SentimentClassifier
{
    private:
        vector<string> negwords;
        vector<string> poswords;
    public: 
        void train(vector<DSString*>); //Read in training data and indentify words with certain sentiments.
        void predict(vector<DSString*>); //Read in a dataset and assign 
        float analyze(vector<Tweet>, vector<DSString*>); //Check accuracy
};

#endif