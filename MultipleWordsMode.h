#ifndef MULTIPLEWORDSMODE_H
#define MULTIPLEWORDSMODE_H

#include "Stage.h"
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

class MultipleWordsMode : public Stage {
protected:
    vector<int> xCoordinates;     // Stores x-coordinates for each word
    vector<int> yCoordinates;     // Stores y-coordinates for each word
    vector<string> displayedWords; // Stores currently displayed words
    int numberOfWords;            // Number of words to display simultaneously

    // Initializes coordinates for words and selects initial words
    void initializeWordsCoordinates();
public:
    static const int MAX_ATTEMPTS; // Maximum number of attempts to find a suitable x coordinate
    
    // Constructor
    MultipleWordsMode(int initialTargetScore, int initialDropSpeed, const string& initialFileName, int numWords);

    // Overridden function to print mode information
    void printModeInfo() const override;

    // Main game logic for Multiple Words Mode
    virtual bool runGame() override;
};

#endif // MULTIPLEWORDSMODE_H

