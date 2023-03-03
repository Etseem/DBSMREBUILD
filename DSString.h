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
        friend std::istream &operator>>(std::istream &in, DSString &c);
        friend std::ostream &operator<<(std::ostream &, const DSString &);
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
        long id;
        vector<string> wordvector2;
        char *data;
};

#endif