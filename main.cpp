#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "DSString.h"
//#include <string>

using namespace std;

int main(int argc, char** argv)
{  
    
    vector<DSString> storage2; //Stores training dataset
    vector<DSString> storage1; //Stores test dataset
    vector<DSString> storage; //Stores non sentiment test dataset

    fstream fout;

    //Read in sentiment test dataset
    char filename[] = "test_dataset_sentiment_10k.csv";
    FILE *stream;
    char buffer[1001];
    size_t maxlen = 1000;

    size_t nread;

    stream = fopen(filename, "r");

    if(stream == NULL)
    {
        cerr << "Opening the file failed!" << endl;
        return(-1);
    }

    
 
    

   //Read non sentiment test dataset

    fout.open("test_dataset_10k.csv", ios::in);

    if(fout.fail())
    {
        cerr << "Opening the file failed!" << endl;
        return -1;
    }


    string foo, foo1, foo2, foo3, foo4; //Dummy strings for getline
    bool firsttime = true;
    do
    {
        getline(fout, foo, ','); //Read in ID
        getline(fout, foo1, ','); //Read in Date
        getline(fout, foo2, ','); //Read in Query
        getline(fout, foo3, ','); //Read in User
        getline(fout, foo4); //Read until the end of the line.

        const char *inp = foo4.c_str();
        DSString newdsstring(inp);
        newdsstring.addID(foo);
        firsttime == false;
        storage.push_back(newdsstring);

    }while(fout.good());

    //Storage.at(0) is the first line. Do not call under any circumstances :]
    //The following is an example of how to use the array.
    DSString teststring = storage.at(3);

    teststring.convertToWords();

    cout << "ID TEST: " << teststring.wordvector2.at(0) << endl;
    
    fclose(stream);

   //Clean up
   storage.clear();
   

    
    return(0);
}