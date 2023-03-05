#include "DSString.h"
#include "Tweet.h"
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

DSString::DSString() //Constructor
{
    len = 0;
    data = nullptr;
    sentiment = -1;
    predictedSentiment = -1;
    id = -1;
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

DSString::DSString(string s) //Converts strings into char arrays
{
    char chararray[s.length()+1];

    strcpy(chararray, s.c_str());

    data = chararray;
    len = sizeof(chararray);

/*
    for(int x=0; x<len; x++)
    {
        cout << data[x] << endl;
    }
*/
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

DSString DSString::substring(size_t start, size_t numChars) const //Create a substring
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

char &DSString::operator[](int index) //Return index
{
    return this->data[index];
}

DSString DSString::operator+(const DSString &addstring)  //Append strings together
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

Tweet DSString::convertToTweet()
{
    Tweet newtweet;

    for(int x=0; x<1; x++)
    {   
            //Determine Sentiment Value.
            if(data[x] == 48)
            {
                newtweet.setSentiment(0);
            }
            else if(data[x] == 52)
            {
                newtweet.setSentiment(4);
            }

            //Find ID.
            int firstdigit = data[x+2] - '0';
            int seconddigit = data[x+3] - '0';
            int thirddigit = data[x+4] - '0';
            int fourthdigit = data[x+5] - '0';
            int fifthdigit = data[x+6] - '0';
            int sixthdigit = data[x+7] - '0';
            int seventhdigit = data[x+8] - '0';
            int eigthdigit = data[x+9] - '0';
            int ninthdigit = data[x+10] - '0';
            int tenthdigit = data[x+11] - '0';
            //Extremely roundabout way to append ints to each other without converting them to strings. Using ints overflows.
            long lon1, lon2, lon3, lon4, lon5, lon6, lon7, lon8, lon9, lon10;
            lon1 = firstdigit * 1000000000;
            lon2 = seconddigit * 100000000;
            lon3 = thirddigit * 10000000;
            lon4 = fourthdigit * 1000000;
            lon5 = fifthdigit * 100000;
            lon6 = sixthdigit * 10000;
            lon7 = seventhdigit * 1000;
            lon8 = eigthdigit * 100;
            lon9 = ninthdigit * 10;
            lon10 = tenthdigit;
            long calculatedID = lon1 + lon2 + lon3 + lon4 + lon5 + lon6 + lon7 + lon8 + lon9 + lon10;

            newtweet.setID(calculatedID);
    }       

    return newtweet;
}

void DSString::convertToWords()
{
    string output = "";
    //string str(data);
    int foo = 0;
    vector<string> wordvector;
    string input = data;

    while(input.compare(output) != 0)
    {
        auto index = input.find_first_of(" ");
        output = input.substr(0,index);

        input = input.substr(index+1, input.length());
        
        if(output.length() == 0)
        {
            continue;
        }
        wordvector2.push_back(output);
        //wordvector3.push_back(&output);
    }

}

void DSString::addID(string s)
{
char chararray[s.length()];
strcpy(chararray, s.c_str());
            
            int firstdigit = chararray[0] - '0';
            int seconddigit = chararray[1] - '0';
            int thirddigit = chararray[2] - '0';
            int fourthdigit = chararray[3] - '0';
            int fifthdigit = chararray[4] - '0';
            int sixthdigit = chararray[5] - '0';
            int seventhdigit = chararray[6] - '0';
            int eigthdigit = chararray[7] - '0';
            int ninthdigit = chararray[8] - '0';
            int tenthdigit = chararray[9] - '0';

           
           long lon1, lon2, lon3, lon4, lon5, lon6, lon7, lon8, lon9, lon10;
            lon1 = firstdigit * 1000000000;
            lon2 = seconddigit * 100000000;
            lon3 = thirddigit * 10000000;
            lon4 = fourthdigit * 1000000;
            lon5 = fifthdigit * 100000;
            lon6 = sixthdigit * 10000;
            lon7 = seventhdigit * 1000;
            lon8 = eigthdigit * 100;
            lon9 = ninthdigit * 10;
            lon10 = tenthdigit;
            //Extremely roundabout way to append ints to each other without converting them to strings. Using ints overflows.
            long calculatedID = lon1 + lon2 + lon3 + lon4 + lon5 + lon6 + lon7 + lon8 + lon9 + lon10;
            
            //int calculatedID = firstdigit + seconddigit + thirddigit + fourthdigit + fifthdigit + sixthdigit + seventhdigit + eigthdigit + ninthdigit + tenthdigit;
            //cout << "Setting ID to: " << calculatedID << endl;
            id = calculatedID;
}
