#ifndef WORDMANAGER_H
#define WORDMANAGER_H

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <unordered_map>
#include <algorithm>
using namespace std;

class WordManager {
private:
    vector<string> words; // Stores all the words
    unordered_map<string, std::chrono::high_resolution_clock::time_point> wordAppearTimes; // Tracks when each word appeared

public:
    // Loads words from a file
    void loadWords(const string& fileName);
    
    // Selects and returns a random word
    string selectRandomWord();
    
    // Returns the number of words loaded
    size_t getWordCount() const;
    
    // Return the number of times a word has appeared
    auto getWordAppearTime(const string& word) const -> decltype(wordAppearTimes.find(word)->second);
    
	// Function to move and display the word on the screen
    void wordMove(string content, int x, int y, int dropSpeed = 1);
    
    // Clear the word from the screen
    void wordErase(string content, int x, int y);
};

#endif // WORDMANAGER_H

