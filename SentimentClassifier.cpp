#include "SentimentClassifier.h"
#include "Tweet.h"
#include "DSString.h"
#include <iostream>
#include <vector>
using namespace std;


void SentimentClassifier::train(vector<DSString*> dataset) //Determine what words are positive and negative.
{

    vector<string> negativewords;
    vector<string> positivewords;
    vector<int> negToDel;
    vector<int> posToDel;

    DSString foo = *dataset.at(1);

    for(int x = 1; x<dataset.size(); x++) //Iterate through the entire dataset
    {
        


        if(dataset.at(x)->sentiment == 0) //Negative sentiment handling
        {
            for(int y = 0; y<dataset.at(x)->wordvector2.size(); y++)
            {
                //Put all words in that tweet into the negative words vector.
                cout << "Pushed back: " << dataset.at(x)->wordvector2.at(x) << endl;
                negativewords.push_back(dataset.at(x)->wordvector2.at(x));
            }
        }
        else if(dataset.at(x)->sentiment == 4) //Positive sentiment handling
        {
            for(int y = 0; y<dataset.at(x)->wordvector2.size(); y++)
            {
                //Put all words in that tweet into the positive words vector.
                positivewords.push_back(dataset.at(x)->wordvector2.at(x));
            }
        }

    //Discover neutral words by finding words that are in common. If they are in common, remove from both vectors.
    //Check every X with every Y.

    

    for(int x=0; x<negativewords.size(); x++)
    {
        for(int y=0; y<positivewords.size(); y++)
        {
            if(positivewords.at(y) == negativewords.at(x)) //If equal, delete them both. Since I don't want to change the sizes while it's running, I'll make an vector of indexes to delete.
            {
                negToDel.push_back(x);
                posToDel.push_back(y);
            }
        }
    }

    

    //Delete all words in common.

    for(int x=negToDel.size(); x>0; x++)
    {
    //Start at the end of the vector so we don't displace the values at the start.
    negativewords.erase((negativewords.begin() + negToDel.back()));
    negToDel.pop_back();
    }
    for(int x=posToDel.size(); x>0; x++)
    {
    //Start at the end of the vector so we don't displace the values at the start.
    positivewords.erase((positivewords.begin() + posToDel.back()));
    posToDel.pop_back();
    }
    
    //And now we have a list of words that only appear in "positive" tweets and words that only appear in "negative" tweets.

    


    this->poswords = positivewords;
    this->negwords = negativewords;

    



    }

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
        else //If completely neutral, predict positive (4)
        {
            dataset.at(x)->predictedSentiment = 4;
        }
    }
}

/*
    cout << "Positive words:" << endl;

    for(int x=0; x<positivewords.size(); x++)
    {
        cout << positivewords.at(x) << endl;
    }

    cout << "Negative words:" << endl;

    for(int x=0; x<negativewords.size(); x++)
    {
        cout << negativewords.at(x) << endl;
    }


*/