#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool is_valid(const std::string& word, const std::set<std::string>& dict);
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string& partialWord, int usedCount[], int position, set<std::string>& result);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> result;
    std::string partialWord(in.length(), '-');
    int floatingCount[26] = {0};

    for(int i=0; i < floating.size(); ++i){
        char character = floating[i];
        floatingCount[character - 'a']--;
    }
    wordleHelper(in, floating, dict, partialWord, floatingCount, 0, result);
    return result;
}

// Define any helper functions here
bool is_valid(const std::string& word, const std::set<std::string>& dict)
{
    return dict.find(word) != dict.end();
}

void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string& partialWord, int usedCount[], int position, set<std::string>& result)
{
    // bc. partial word is complete
    if(position == in.length()){
        bool done = true;
        for(int i=0; i < 26; ++i){
            if(usedCount[i] < 0){
                done = false;
                break;
            }
        }
        if(done && is_valid(partialWord, dict)){
            result.insert(partialWord);
        }
        return;
    }

    if(in[position] != '-'){
        char fixedLetter = in[position];
        partialWord[position] = fixedLetter;
        wordleHelper(in, floating, dict, partialWord, usedCount, position+1, result);
    }
    else {
        for(char character='a'; character <= 'z'; ++character){
            partialWord[position] = character;
            int curr = character - 'a';
            usedCount[curr]++;
            wordleHelper(in, floating, dict, partialWord, usedCount, position+1, result);
            usedCount[curr]--;
    }
    }
}
