#ifndef STAGE_H
#define STAGE_H

#include "WordManager.h"
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

class Stage {
protected:
    string modeName; // Name of the stage mode
    int targetScore; // Target score for this stage
    int dropSpeed; // Speed at which words drop down the screen
    string fileName; // File name from which to load words
    int x, y; // Current position (x,y) of the dropping word
    string content; // The word currently dropping
    string userInput; // Input collected from the user
    WordManager words; // Instance of WordManager to handle word operations

    // Function to play a sound effect
    void playSoundEffect(int frequency, int duration);
    // Function to change the text color in the console
    void setConsoleTextColor(int color);

public:
    // Constructor
    Stage(int initialTargetScore, int initialDropSpeed, const string& initialFileName);

    // Virtual function to display information about the stage
    virtual void printModeInfo() const;

    // Function to end the stage
    void endStage();

    // Function to set the initial position of a new word
    void wordInitialPlace(int &x, int &y);

    // Virtual function to run the game stage
    virtual bool runGame();
};

#endif // STAGE_H

