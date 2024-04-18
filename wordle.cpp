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
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string& partialWord, std::map<char, int>& usedCount, int position, set<std::string>& result);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> result;
    std::string partialWord(in.length(), '-');
    std::map<char, int> floatingCount;

    for(char character : floating){
        floatingCount[character]--;
    }
    wordleHelper(in, floating, dict, partialWord, floatingCount, 0, result);
    return result;
}

void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::string& partialWord, std::map<char, int>& usedCount, int position, set<std::string>& result)
{
    // bc. partial word is complete
    if(position == in.length()){
        bool done = true;
        for(auto& pair : usedCount){
            if(pair.second < 0){
                done = false;
                break;
            }
        }
        if(done && dict.find(partialWord) != dict.end()){
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
            usedCount[character]++;
            wordleHelper(in, floating, dict, partialWord, usedCount, position+1, result);
            usedCount[character]--;
    }
    }
}