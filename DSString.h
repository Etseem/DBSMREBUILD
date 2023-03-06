#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <vector>
#include "Tweet.h"

using namespace std;

class DSString
{
    private:
        int len;
        
    public: //In order of when I implemented them
        DSString();
        DSString(const char *);
        DSString(string);
        //friend istream &operator>>(std::istream &in, DSString &c);
        friend ostream &operator<<(std::ostream &, const DSString &);
        DSString substring(size_t start, size_t numChars) const;
        DSString operator=(const DSString &);
        bool operator==(const DSString &) const;
        ~DSString();
        int length() const;
        DSString(const DSString &);
        char& operator[](int index);
        DSString operator+(const DSString &);
        char *c_str() const;
        DSString toLower() const;
        Tweet convertToTweet();
        void convertToWords();
        void addID(string);

        //End of Methods
        long id;
        vector<string> wordvector2;
        vector<string*> wordvector3;
        char *data;
        int sentiment; //For training data, the ACTUAL sentiment value.
        int predictedSentiment; //For assigning what the program thinks this tweet's sentiment is.
};

#endif