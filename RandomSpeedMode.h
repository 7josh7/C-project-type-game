#ifndef RANDOMSPEEDMODE_H
#define RANDOMSPEEDMODE_H

#include "MultipleWordsMode.h"
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

class RandomSpeedMode : public MultipleWordsMode {
protected:
    vector<int> speed; // Stores drop speed for each word
    const int maxSpeed; // Maximum drop speed
public:
    // Constructor
    RandomSpeedMode(int initialTargetScore, int initialDropSpeed, const string& initialFileName, int numWords, const int maxSpeed);
    
    // Initializes speed for each word
    void initializeWordsSpeed();
    
    // Overridden function to print mode information
    void printModeInfo() const override;
    
    // Main game logic for Multiple Words Mode
    bool runGame() override;
};

#endif // RANDOMSPEEDMODE_H

