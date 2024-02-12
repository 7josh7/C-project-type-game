#include "RandomSpeedMode.h"
#include "Stage.h"
#include "MultipleWordsMode.h"
#include "WordManager.h"
#include "showInstructions.h"
#include "ConsoleUtility.h"
#include "Globals.h"
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

RandomSpeedMode::RandomSpeedMode(int initialTargetScore, int initialDropSpeed, const string& initialFileName, int numWords, const int maxSpeed)
    : MultipleWordsMode(initialTargetScore, initialDropSpeed, initialFileName, numWords), maxSpeed(maxSpeed) {
    initializeWordsSpeed();
}

void RandomSpeedMode::initializeWordsSpeed() {
    for (int i = 0; i < numberOfWords; ++i) {
        speed.push_back(rand() % maxSpeed + 1);//隨機產生1~3的數字
    }
}

void RandomSpeedMode::printModeInfo() const {
    system("cls"); // Clears the console screen
    cout << "Prepare for Random Speed Words Mode! " << endl;
    Stage::printModeInfo();
}

bool RandomSpeedMode::runGame(){
    userInput = "";
    system("cls"); // 清除控制台（命令提示字元）上的內容
    try {
        words.loadWords(fileName);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading words: " << e.what() << std::endl;
        return false;
    }
    initializeWordsCoordinates();//initial coordinates for words and sotre selected initial words in the displayedWords vector

    // Set game start and end times
    auto startTime = chrono::high_resolution_clock::now();
    auto endTime = startTime + chrono::minutes(1);
    auto currentTime = chrono::high_resolution_clock::now();

    // While time has not run out
    while (chrono::high_resolution_clock::now() < endTime) {
        ConsoleUtility::showInfo(userInput, endTime, targetScore, globalScore);
        // Display words
        for (int i = 0; i < numberOfWords; ++i) {
            words.wordMove(displayedWords[i], xCoordinates[i], yCoordinates[i], speed[i]);
        }
        
        for (int i = 0; i < numberOfWords; ++i) {
            if (yCoordinates[i] < SCREEN_HEIGHT - 1) {
                currentTime = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(currentTime - words.getWordAppearTime(displayedWords[i]));
                yCoordinates[i] = duration.count() * speed[i];
            } else {
            	words.wordErase(displayedWords[i], xCoordinates[i], yCoordinates[i]);
                wordInitialPlace(xCoordinates[i], yCoordinates[i]);
                displayedWords[i] = words.selectRandomWord();
                speed[i] = rand() % maxSpeed + 1;
                globalScore -= 5;
            }
        }
        // Handle keyboard input
        if (_kbhit()) {
            char input = _getch();
            if (input == '\r' || input == '\n') { // Enter key pressed
                bool rightAnswer = false;
                for (int i = 0; i < numberOfWords; ++i) {
                    if (userInput == displayedWords[i]) {// Correct word entered
                        globalScore += 10;
                        playSoundEffect(500, 100); // Play success sound
                        // Reset word position and select new word
                        words.wordErase(displayedWords[i], xCoordinates[i], yCoordinates[i]);
                        wordInitialPlace(xCoordinates[i], yCoordinates[i]);
                        displayedWords[i] = words.selectRandomWord();
                        userInput = "";
                        rightAnswer = true;
                    }
                }

                if (!rightAnswer) {// Incorrect word entered
                    userInput = "";
                    globalScore -= 5; // Penalize
                    playSoundEffect(200, 100); // Play error sound
                }
            } else if (input == '\b' && !userInput.empty()) { // Backspace key pressed
                userInput.pop_back(); // Remove last character from input
            } else {
                userInput += input; // Add character to input
            }
        }

    }

    endStage();
    return globalScore >= targetScore;
}

