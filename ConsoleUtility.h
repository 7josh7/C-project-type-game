#ifndef CONSOLEUTILITY_H
#define CONSOLEUTILITY_H

#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <unordered_map>
#include <algorithm>
using namespace std;

class ConsoleUtility {
public:
    // Sets console cursor position
    static void setConsoleCursorPosition(int x, int y);
    
    // Draws a bottom line across the console
    static void drawBottomLine();
    
    // Shows game info like user input, remaining time, and score
    static void showInfo(const string& userInput, chrono::time_point<chrono::high_resolution_clock> endTime, int targetScore, int globalScore);
};

#endif // CONSOLEUTILITY_H

