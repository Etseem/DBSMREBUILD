#include "SentimentClassifier.h"
#include "Tweet.h"
#include "DSString.h"
#include <iostream>
#include <vector>
#include <algorithm> //Used to std::sort.
#include <set> 
using namespace std;


void SentimentClassifier::train(vector<DSString*> dataset) //Determine what words are positive and negative.
{

    vector<string> negativewords;
    vector<string> positivewords;
    //posToDel and negToDel1 didn't work out. Using sets got me exactly what I wanted more efficiently.
    set<int> negToDel2;
    set<int> posToDel2;


    DSString foo = *dataset.at(1);




    for(int x = 1; x<(dataset.size()-1); x++) //Iterate through the entire dataset
    {
        
        int lim = dataset.at(x)->wordvector2.size();

        if(dataset.at(x)->sentiment == 0) //Negative sentiment handling
        {
            for(int y = 0; y<lim; y++)
            {
                //Put all words in that tweet into the negative words vector.
                negativewords.push_back(dataset.at(x)->wordvector2.at(y));
            }
        }
        else if(dataset.at(x)->sentiment == 4) //Positive sentiment handling
        {
            for(int y = 0; y<lim; y++)
            {
                //Put all words in that tweet into the positive words vector.
                positivewords.push_back(dataset.at(x)->wordvector2.at(y));
            }
        }
    }

    //Discover neutral words by finding words that are in common. If they are in common, remove from both vectors.
    //Check every X with every Y.

    //Clean up data, delete duplicates.

    sort(negativewords.begin(), negativewords.end());
    negativewords.erase(unique(negativewords.begin(),negativewords.end()));

    sort(positivewords.begin(), positivewords.end());
    positivewords.erase(unique(positivewords.begin(), positivewords.end()));


    for(int x=0; x<negativewords.size(); x++)
    {
        for(int y=0; y<positivewords.size(); y++)
        {
            if(positivewords.at(y) == negativewords.at(x)) //If equal, delete them both. Since I don't want to change the sizes while it's running, I'll make an vector of indexes to delete.
            {
                negToDel2.insert(x);
                posToDel2.insert(y);
            }
        }
    }


    //Delete all words in common.

    //Start at the end of the vector so we don't displace the values at the start.


    for(int x=negativewords.size(); x>0; x--)
       {
            auto test = negToDel2.find(x);
            if(test != negToDel2.end())
            {
                negativewords.erase(negativewords.begin() + x);
            }
       }
    

    for(int x=positivewords.size(); x>0; x--)
       {
            auto test = posToDel2.find(x);
            if(test != posToDel2.end())
            {
                positivewords.erase(positivewords.begin() + x);
            }
       }
    
    
    //And now we have a list of words that only appear in "positive" tweets and words that only appear in "negative" tweets.

    this->poswords = positivewords;
    this->negwords = negativewords;
}

void SentimentClassifier::predict(vector<DSString*> dataset)
{


    for(int x=0; x<dataset.size(); x++) //Go through every tweet.
    {
        int negcount = 0;
        int poscount = 0;

        for(int y=0; y<dataset.at(x)->wordvector2.size(); y++) //Check every word
        {
            for(int z=0; z<poswords.size(); z++) //Check every POSITIVE word
            {
                if(dataset.at(x)->wordvector2.at(y) == poswords.at(z))
                {
                    poscount++;
                }
            }
            for(int z=0; z<negwords.size(); z++) //Check every NEGATIVE word
            {
                if(dataset.at(x)->wordvector2.at(y) == negwords.at(z))
                {
                    negcount++;
                }
            }
        }


        if(negcount > poscount) //If more negative, predict 0
        {
            dataset.at(x)->predictedSentiment = 0;
        }
        else if(poscount > negcount) //If more positive, predict 4
        {
            dataset.at(x)->predictedSentiment = 4;
        }
        else //If completely neutral or not in dataset, predict positive (4)
        {
            dataset.at(x)->predictedSentiment = 4;
        }
    }
}

float SentimentClassifier::analyze(vector<Tweet> answerKey, vector<DSString *> predictedTweets) //Determine Accuracy
{

int numCorrect = 0;


for(int x=1; x<answerKey.size(); x++) //Read in the actual answer and predicted
{
    int answer = answerKey.at(x).getSentiment();
    int predictedanswer = predictedTweets.at(x)->predictedSentiment;

if(answer == predictedanswer) //If true, it means that it was correct.
{
    numCorrect++;
}

}

float accuracy = float(numCorrect) / float(answerKey.size());

return accuracy;

}