#include "SentimentClassifier.h"
#include "Tweet.h"
#include "DSString.h"
#include <iostream>
#include <vector>
#include <algorithm> //Used to std::sort.
using namespace std;


void SentimentClassifier::train(vector<DSString*> dataset) //Determine what words are positive and negative.
{

    vector<string> negativewords;
    vector<string> positivewords;
    vector<int> negToDel;
    vector<int> posToDel;

    DSString foo = *dataset.at(1);




    for(int x = 1; x<(dataset.size()-1); x++) //Iterate through the entire dataset
    {
        
        int lim = dataset.at(x)->wordvector2.size();

        if(dataset.at(x)->sentiment == 0) //Negative sentiment handling
        {
            for(int y = 0; y<lim; y++)
            {
                //Put all words in that tweet into the negative words vector.
                //cout << "Pushed back: " << dataset.at(x)->wordvector2.at(y) << endl;
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

    cout << "Done creating positive/negative word vectors!" << endl;
    cout << "Attempting to sort the vectors..." << endl;

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
                cout << "Attempting to push back Neg = " << x << " & Pos = " << y << endl;
                negToDel.push_back(x);
                posToDel.push_back(y);
            }
        }
    }
    cout << "Completed negToDel and posToDel" << endl;
    
    //Clean up and delete duplicates.
    sort(negToDel.begin(), negToDel.end());
    negToDel.erase(unique(negToDel.begin(),negToDel.end()));

    sort(posToDel.begin(), posToDel.end());
    posToDel.erase(unique(posToDel.begin(), posToDel.end()));

    cout << "Cleaned up Pos and Neg to Del!" << endl;

    cout << "# of negativewords: " << negativewords.size() << endl;
    cout << "# of positivewords: " << positivewords.size() << endl;
    cout << "# of negToDel: " << negToDel.size() << endl;
    cout << "# of posToDel: " << posToDel.size() << endl;

    //Delete all words in common.
    cout << "Press ENTER to continue." << endl;
    cin.get();

    for(int x=0; x<negToDel.size()-1; x++)
    {
    //Start at the end of the vector so we don't displace the values at the start.
    if(!negativewords.empty())
    {
        cout << "Attempting to delete something negative!" << endl;
        negativewords.erase((negativewords.begin() + negToDel.back()));
        cout << "Popping back..." << endl;
        negToDel.pop_back();
    }
    else
    {
        cout << "Had to force quit! Debug codes: " << negativewords.size() << " " << negToDel.size() << endl;
    }
    
    }
    for(int x=0; x<posToDel.size(); x++)
    {
    //Start at the end of the vector so we don't displace the values at the start.
    cout << "Attempting to delete something positive!" << endl;
    positivewords.erase((positivewords.begin() + posToDel.back()));
    posToDel.pop_back();
    }

    cout << "Done deleting!" << endl;
    
    //And now we have a list of words that only appear in "positive" tweets and words that only appear in "negative" tweets.

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


    this->poswords = positivewords;
    this->negwords = negativewords;

    



    }

void SentimentClassifier::train2(vector<DSString> &foo)
{


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
    


*/