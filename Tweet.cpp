#include "Tweet.h"
#include <iostream>
using namespace std;

Tweet::Tweet()
{
    id = 0;
    sentiment = 1;
    predictedSentiment = 1;
}


//Getters and Setters
long Tweet::getID()
{
    return id;
}

int Tweet::getSentiment()
{
    return sentiment;
}

int Tweet::getPredicted()
{
    return predictedSentiment;
}

void Tweet::setID(long x)
{
    id = x;
}

void Tweet::setSentiment(int x)
{
    sentiment = x;
}

void Tweet::setPredicted(int x)
{
    predictedSentiment = x;
}
