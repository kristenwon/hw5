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
    std::string partialWord = in;
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
        if(floating.empty() && dict.find(partialWord) != dict.end()){
            result.insert(partialWord);
        }
        return;
    }

    if(in[position] != '-'){
        partialWord[position] = in[position];
        wordleHelper(in, floating, dict, partialWord, usedCount, position+1, result);
    }
    else {
        int numdash = 0;
        for(char c : partialWord){
            if(c == '-'){
                numdash++;
            }
        }
        if(floating.size() == numdash){
            for(int i=0; i < floating.size(); i++){
                partialWord[position] = floating[i];
                string newFloating = floating;
                newFloating.erase(i, 1);
                wordleHelper(in, newFloating, dict, partialWord, usedCount, position+1, result);
            }
        }
        else {
            for(char c = 'a'; c <= 'z'; c++){
                partialWord[position] = c;
                if(usedCount[c] < 0){
                    string newFloating = floating;
                    int pos = newFloating.find(c);
                    if(pos != string::npos){
                        newFloating.erase(pos, 1);
                    }
                    wordleHelper(in, newFloating, dict, partialWord, usedCount, position+1, result);
                }
                else {
                    wordleHelper(in, floating, dict, partialWord, usedCount, position+1, result);
                }

            }
        }
        partialWord[position] = '-';
    }
}