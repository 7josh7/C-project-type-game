#include "Stage.h"
#include "MultipleWordsMode.h"
#include "RandomSpeedMode.h"
#include "WordManager.h"
#include "showInstructions.h"
#include "ConsoleUtility.h"
#include "Globals.h"
#include <windows.h>
#include <stdexcept>
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

int main(){
    srand(static_cast<unsigned>(time(nullptr)));
    int choice = 1;
    int nextMode = 1; // The next game mode that the user has to play
    bool passed;
    nextMode = showInstructions(nextMode); // Display the game instructions
    do {
        // Stages initialization
        Stage stage_1(STAGE_1_TARGET_SCORE, 1, "words.txt");
        MultipleWordsMode stage_2(STAGE_2_TARGET_SCORE, 1, "words.txt", 3);
        RandomSpeedMode stage_3(STAGE_3_TARGET_SCORE, 1, "words.txt", 2, 3);
        RandomSpeedMode stage_4(STAGE_4_TARGET_SCORE, 1, "words.txt", 4, 4);
        // Hide the console cursor
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 100;
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
        system("cls");
        if (nextMode != -1) {
            choice = nextMode; // The user has to play the next game mode
        } else {
            // The user can choose the game mode
            system("cls");
            cout << "!!!The God Like Mode is unlocked!!!" << endl;
            cout << "Choose a game mode:" << endl;
            cout << "1. Standard Mode" << endl;
            cout << "2. Multi-Vocab Mode" << endl;
            cout << "3. Random Speed Mode" << endl;
            cout << "4. God Like Mode" << endl;
            cout << "0. Exit" << endl;
            do {
                cout << "Enter your choice: ";
                cin >> choice;
                // Clear error state and ignore invalid input
                if (cin.fail()) {
                    cin.clear(); // Clear error state
                    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');; // Clear input buffer
                    cout << "Invalid input, please enter a number." << endl;
                    choice = -1;
                    continue;
                }

                // Check if choice is out of valid range
                if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 0) {
                    cout << "Invalid choice, please try again: ";
                }
            } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 0);
        }
        try {
            switch (choice) {
                case 1:
                    system("cls");
                    stage_1.printModeInfo();
                    passed = stage_1.runGame();
                    break;
                case 2:
                    stage_2.printModeInfo();
                    passed = stage_2.runGame();
                    break;
                case 3:
                    stage_3.printModeInfo();
                    passed = stage_3.runGame();
                    break;
                case 4:
                    stage_4.printModeInfo();
                    passed = stage_4.runGame();
                    break;
                case 0:
                    cout << "Exiting game." << endl;
                    passed = true;
                    break;
            }
            if (!passed) {
                choice = 1;
                nextMode = 1;
                globalScore = 0;
                nextMode = showInstructions(nextMode);
            }
        } catch (const runtime_error& e) {
            cerr << "Error: " << e.what() << endl;
            // Handle the error (e.g., exit the program, try a different file, etc.)
        }

        if (choice != 0 && passed == true) {
            nextMode = choice + 1; // The next game mode that the user has to play
            if (nextMode > 3) {
                cout << "!!!You are the king of the word!!!" << endl;
                cout << "Press Enter to continue...";
                nextMode = -1; // Reset the game mode
                cin.get();
            }
        }
    } while (choice != 0);

    return 0;
}
