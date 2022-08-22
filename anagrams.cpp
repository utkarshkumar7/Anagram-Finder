//  anagrams.cpp
//  CS32 Project 3
#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

//FUNCTION PROTOTYPING/DEFINITIONS
int makeDictionary(istream &dictfile, string dict[]);
int shuffleChars(string word, const string dict[], int size, string results[]);
void revealOutcomes(const string results[], int size);

//ADDITIONAL FUNCTIONS/HELPERS
int makeDictionaryHelper(istream &dictfile, string dict[], int &lineCount);
int shuffleCharsHelper(string word, const string dict[], int size, string results[], int &count);
void revealOutcomesHelper(const string results[], int size, int count);
void loopPermutations(int i, int max, string prefix, string rest, string word, const string dict[], int size, string results[], int &count);
bool checkExistence(string word, const string results[], int size);
void permutationChecker(string word, const string dict[], int size, string results[], int &count, string prefix, string rest);
bool crossChecker(string word, const string dict[], int size, string results[], int &count);

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

int main()
{
    //ANAGRAMS.CPP
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

    dictfile.open("/Users/utkarshk2002/Desktop/CS32_Proj3/words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = makeDictionary(dictfile, dict);
    cout << "There are " << nwords << " words in this dictionary" << endl;


    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = shuffleChars(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        revealOutcomes(results, numMatches);

    return 0;

}
 
//FUNCTION IMPLEMENTATIONS

//1. Make dictionary function
//Puts each string in dictfile into the array dict. Returns the number of words
//read into dict. This number should not be larger than MAXDICTWORDS since that is
//the size of the array.
int makeDictionaryHelper(istream &dictfile, string dict[], int &lineCount)
{
    string line;
    //BASE CASE: If we reach the end of the file OR maximum number of words that dict can hold
    if (lineCount >= MAXDICTWORDS || dictfile.eof())
        //We return the number of words present
        return lineCount;
    else
    {
        //Use the getline function to store the value of the string into temp variable line
        getline(dictfile, line);
        //Set the
        dict[lineCount] = line;
        lineCount++;
    }
 
    return makeDictionaryHelper(dictfile, dict, lineCount);
}

int makeDictionary(istream &dictfile, string dict[])
{
    int lineCount = 0;
    return makeDictionaryHelper(dictfile, dict, lineCount);
}

//2. Shuffle characters function

// Puts all the possibilities of word which are found in dict into results. Returns
// the number of matched words found. This number should not be larger than
// MAXRESULTS since that is the size of the array. The size is the number of words
// inside the dict array.

bool checkExistence(string word, const string array[], int size)
{
    if(size == 0) return false;
    return (array[0] == word || checkExistence(word, array + 1, size-1));
}

void loopPermutations(int i, int max, string prefix, string rest, string word, const string dict[], int size, string results[], int &count)
{
    if (i >= max) return;
    string newPrefix = prefix + rest.substr(i,1);
    string newRest = rest.substr(0,i) + rest.substr(i + 1, rest.size());
    permutationChecker(word, dict, size, results, count, newPrefix, newRest);
    loopPermutations(i + 1, max, prefix, rest, word, dict, size, results, count);
}

bool crossChecker(string word, const string dict[], int size, string results[], int &count)
{
    return (checkExistence(word, dict, size) && !checkExistence(word, results, count) && count < MAXRESULTS);
}

void permutationChecker(string word, const string dict[], int size, string results[], int &count, string prefix, string rest)
{
    //The below code is taken from the printPermutations function and modified with extra parameters
    if(rest.size() == 0){
        //RUN A LOOP TO CROSS-CHECK WITH DICT AND THEN ADD TO ARRAY IF not already in results
        if(crossChecker(prefix, dict, size, results, count))
        {
            results[count] = prefix;
            count++;
        }}
    else
    {
        //Continue to make permutations until we have made all possible ones
        loopPermutations(0, (int) rest.size(), prefix, rest, word, dict, size, results, count);
    }
}


int shuffleCharsHelper(string word, const string dict[], int size, string results[], int &count)
{
    //The below code is taken from the printPermutations function and modified with extra parameters
    permutationChecker(word, dict, size, results, count, "", word);
    return count;
}

int shuffleChars(string word, const string dict[], int size, string results[])
{
    //HERE COUNT IS USED AS THE SIZE OF THE RESULTS ARRAY
    int count = 0;
    return shuffleCharsHelper(word, dict, size, results, count);
}

// 3. Reveal outcomes function

// Displays size number of strings from results. The results can be printed in
// any order.
void revealOutcomes(const string results[], int size)
{
    return revealOutcomesHelper(results, size, 0);
}

void revealOutcomesHelper(const string results[], int size, int count)
{
    if(count == size && size <= MAXRESULTS) return;
    else if (count == MAXRESULTS) return;
    else
    {
        cout << "Matching word " << results[0] << endl;
        count++;
        revealOutcomesHelper(results + 1, size, count);
    }
}

//ADDITIONAL FUNCTIONS USED
//LOOP FOR printPermutations
/*
 
 void printPermutations(string prefix, string rest)
 {
     if(rest.size() == 0)
         //RUN A LOOP TO CROSS-CHECK WITH DICT AND THEN ADD TO ARRAY
         cout << prefix << endl;
     else
     {
         loopPermutations(0, (int) rest.size(), prefix, rest);

     }
 }

        for (int i = 0; i < rest.length(); i++)
        {
            string newPrefix = prefix + rest.at(i);
            string newRest = rest.substr(0, i) + rest.substr(i + 1);
            printPermutations(newPrefix, newRest);
        }
 
 
 //This function shortens the dictionary to contain only words of the same length as inputted parameter
 void dictShortener(const string dict[], int size, string dictNew[], int &newSize, string word)
 {
     if(size == 0 || dict[0] == "") return; //Reached the end of the dictionary
     if(dict[0].size() == word.size()) //If the size is equal we proceed to add it to the shortened dictionary array
     {
         dictNew[newSize] = dict[0];
         newSize++;
     }
     return dictShortener(dict+1, size-1, dictNew, newSize, word); //Recursive call to next iteration
 }

*/
