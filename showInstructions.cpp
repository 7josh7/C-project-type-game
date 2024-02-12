#include "showInstructions.h"
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

int showInstructions(int& nextMode){
    system("cls"); // Clear the console screen
    string input;
    cout << "\n Welcome to the exhilarating Word Drop Game! \n\n";
    cout << " Your mission, should you choose to accept it, is to type the words that are dropping down your screen. Be quick, because if they reach the bottom, there will be a penalty!\n\n";
    cout << " Each correct word you type will earn you points, boosting your score to the stars! But beware, any mistake will cost you. So keep your eyes peeled and your fingers ready!\n\n";
    cout << " You have 1 minute to prove your typing prowess. Your final score will be a combination of your correct words and any penalties for mistakes.\n\n";
    cout << " The game has three modes, each harder than the last:\n";
    cout << " 1. Standard Mode: A gentle introduction to the game. Perfect for beginners.\n";
    cout << " 2. Multi-Vocab Mode: A tougher challenge. Multiple words will drop at the same time.\n";
    cout << " 3. Random Speed Mode: The ultimate test. Words drop at random speeds. Only the best will survive.\n\n";
    cout << " Good luck!\n\n";
    cout << " Ready for the challenge? Press Enter to start your adventure...\n";
    getline(cin, input); // Get the whole line of input
    if (input == "I am the king of the word"|| input == "i am the king of the word" || input == "-1") {
        return -1; // Special value to indicate that the user can choose the game mode
    } else {
        return nextMode; // The next game mode that the user has to play
    }
}


