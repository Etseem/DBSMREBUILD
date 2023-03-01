#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>

using namespace std;

class DSString
{
    private:
        int len;
        char *data;
    public: //In order of when I implemented them
        DSString();
        DSString(const char *);
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
        void edit(char*);
        char *c_str() const;
        DSString toLower() const;

};

#endif