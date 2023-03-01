#include "DSString.h"
#include <iostream>
#include <string.h>
using namespace std;

DSString::DSString() //Constructor
{
    len = 0;
    data = nullptr;
}

DSString::DSString(const char * str) //Constructor that converts a Cstring
{
    //Determine size of the string.
    int size = 0;
    while (str[size] != '\0') size++;
    len = size;

    //Create a new data value with the exact size of the string.
    data = new char[len];

    //Set data at index equal to the string's value at the index.
    for(int x=0; x < len; x++)
    {
        data[x] = str[x];
        // data[x] = *(str + x);
    }
}

std::istream &operator>>(std::istream &in, DSString &c) //Input stream? Come back to this later
{
    return in;
}

std::ostream &operator<<(std::ostream &s, const DSString &input) // Output
{
    for(int x=0; x<input.len; x++)
    {
        cout << input.data[x];
    }
    return s;
}

DSString DSString::substring(size_t start, size_t numChars) const
{
    int charsprinted = 0; //Used as a counter
    DSString newdsstring; //Create a new array

    newdsstring.len = numChars;
    newdsstring.data = new char[numChars];

    for(int x=start; charsprinted<numChars; x++)
    {
        if(x>len)
        {
            x = 0;
        }
        newdsstring.data[x-start] = this->data[x];
        charsprinted++;
    }

    return newdsstring;
}

DSString DSString::operator=(const DSString &copydstring) // Copy
{
    delete data;

    this->len = copydstring.len;
    data = new char[len];
    for(int x=0; x < len; x++)
    {
        data[x] = copydstring.data[x];
    }

    return DSString();
}

bool DSString::operator==(const DSString &compstr) const //Check if Dstrings are the exact same
{
    bool discrep = true;

    if(this->len != compstr.len)
    {
        discrep = false;
    }
    else
    {
        for(int x=0; x<len; x++)
        {
            if(data[x] != compstr.data[x])
            {
                discrep = false;
            }
        }
    }

    return discrep;
}

DSString::~DSString() //Destructor
{
    delete data;
}

int DSString::length() const //Returns length
{
    return len;
}

DSString::DSString(const DSString &copydstring) //Copy constructor
{
    this->len = copydstring.len;
    data = new char[len];
    for(int x=0; x < len; x++)
    {
        data[x] = copydstring.data[x];
    }
}

char &DSString::operator[](int index)
{
    return this->data[index];
}

DSString DSString::operator+(const DSString &addstring) 
{
    //Create temp variables
    int newlen = len + addstring.len;
    char *tempdata = new char[newlen];
    for(int x=0; x<len; x++) //Add original string to temp
    {
        tempdata[x] = data[x];
    }
    for(int x=0; x<addstring.len; x++) //Append new string to temp
    {
        tempdata[x+len] = addstring.data[x];
    }

    //Write new data and length
    delete data;
    len = newlen;
    data = tempdata;

    return *this;
}

void DSString::edit(char* input)
{
}

char *DSString::c_str() const //Return a pointer to data
{
    return data;
}

DSString DSString::toLower() const //Convert all alphabet to lowercase.
{
    for(int x=0; x<len; x++)
    {
    
    if(data[x] >= 65 && data[x] <= 90)
    {
        data[x] = char(data[x]+32);
    }

    }

    return *this;
}
