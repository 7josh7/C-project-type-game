#include "Stage.h"
#include "MultipleWordsMode.h"
#include "RandomSpeedMode.h"
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

const int MultipleWordsMode::MAX_ATTEMPTS = 1000;

MultipleWordsMode::MultipleWordsMode(int initialTargetScore, int initialDropSpeed, const string& initialFileName, int numWords)
    : Stage(initialTargetScore, initialDropSpeed, initialFileName), numberOfWords(numWords) {}
        
void MultipleWordsMode::initializeWordsCoordinates() {
    // Loop for each word
    for (int i = 0; i < numberOfWords; ++i) {
        int x, y;
        // Select a random word
        string word = words.selectRandomWord();
        // Keep generating new coordinates until a unique x coordinate is found
        int attempts = 0;
        do {
            if (++attempts > MAX_ATTEMPTS) {
                throw std::runtime_error("Unable to find suitable coordinates for all words");
            }
            // Generate initial place for the word
            wordInitialPlace(x, y);
            bool isOverlap = false;
            // Loop through all existing x coordinates
            for (int j = 0; j < xCoordinates.size(); ++j) {
                // Check if the new x coordinate or the new x coordinate plus the word length is within the range of any existing x coordinate and its corresponding word length
                if ((x >= xCoordinates[j] && x <= xCoordinates[j] + displayedWords[j].size()) ||
                    (xCoordinates[j] >= x && xCoordinates[j] <= x + word.size()) ||
                    (x + word.size() >= xCoordinates[j] && x + word.size() <= xCoordinates[j] + displayedWords[j].size())) {
                    // If there is an overlap, set the flag to true and break the loop
                    isOverlap = true;
                    break;
                }
            }
            // If there is no overlap, add the x coordinate to the list and break the loop
            if (!isOverlap) {
                xCoordinates.push_back(x);
                break;
            }
        // Continue generating new coordinates until a unique x coordinate is found
        } while (true);
        // Add the y coordinate for the word
        yCoordinates.push_back(y);
        // Add the selected word to the list of displayed words
        displayedWords.push_back(word);
    }
}

void MultipleWordsMode::printModeInfo() const{
    system("cls"); // Clears the console screen
    cout << "Prepare for Multiple Words Mode! " << endl;
    Stage::printModeInfo();
}

bool MultipleWordsMode::runGame(){
    userInput = "";
    system("cls"); // Clears the console screen
    try {
        words.loadWords(fileName);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading words: " << e.what() << std::endl;
        return false;
    }
    initializeWordsCoordinates(); // Initialize coordinates for words and store selected initial words

    // Set game start and end times
    auto startTime = chrono::high_resolution_clock::now();
    auto endTime = startTime + chrono::minutes(1);
    auto currentTime = chrono::high_resolution_clock::now();

    // While time has not run out
    while (chrono::high_resolution_clock::now() < endTime) {
        ConsoleUtility::showInfo(userInput, endTime, targetScore, globalScore);
        // Display words
        for (int i = 0; i < numberOfWords; ++i) {
            words.wordMove(displayedWords[i], xCoordinates[i], yCoordinates[i]);
        }

    // Update the position of each word
    for (int i = 0; i < numberOfWords; ++i) {
        if (yCoordinates[i] < SCREEN_HEIGHT - 1) {
            currentTime = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(currentTime - words.getWordAppearTime(displayedWords[i]));
            yCoordinates[i] = duration.count() * dropSpeed;
        } else {
            int attempts = 0;
            do {
                if (++attempts > MAX_ATTEMPTS) {
                    throw std::runtime_error("Unable to find suitable coordinates for new word");
                }
                // Generate initial place for the word
                words.wordErase(displayedWords[i], xCoordinates[i], yCoordinates[i]);
                wordInitialPlace(xCoordinates[i], yCoordinates[i]);
                bool isOverlap = false;
                // Loop through all existing x coordinates
                for (int j = xCoordinates.size() - numberOfWords; j < xCoordinates.size(); ++j) {
                    if (j == i) continue; // Skip checking against itself
                    // Check if the new x coordinate or the new x coordinate plus the word length is within the range of any existing x coordinate and its corresponding word length
                    if ((xCoordinates[i] >= xCoordinates[j] && xCoordinates[i] <= xCoordinates[j] + displayedWords[j].size()) ||
                        (xCoordinates[j] >= xCoordinates[i] && xCoordinates[j] <= xCoordinates[i] + displayedWords[i].size()) ||
                        (xCoordinates[i] + displayedWords[i].size() >= xCoordinates[j] && xCoordinates[i] + displayedWords[i].size() <= xCoordinates[j] + displayedWords[j].size())) {
                        // If there is an overlap, set the flag to true and break the loop
                        isOverlap = true;
                        break;
                    }
                }
                // If there is no overlap, break the loop
                if (!isOverlap) {
                    break;
                }
            } while (true);
            displayedWords[i] = words.selectRandomWord();
            userInput = "";
            globalScore -= 5; // Penalize for missed word
        }
    }

        // Handle keyboard input
        if (_kbhit()) {
            char input = _getch();
            if (input == '\r' || input == '\n') { // Enter key pressed
                bool rightAnswer = false;
                for (int i = 0; i < numberOfWords; ++i) {
                    if (userInput == displayedWords[i]) { // Correct word entered
                        globalScore += 10;
                        playSoundEffect(500, 100); // Play success sound
                        // Clear the word from the screen and reset position
                        words.wordErase(displayedWords[i], xCoordinates[i], yCoordinates[i]);
                        wordInitialPlace(xCoordinates[i], yCoordinates[i]);
                        displayedWords[i] = words.selectRandomWord();
                        userInput = "";
                        rightAnswer = true;
                    }
                }

                if (!rightAnswer) { // Incorrect word entered
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

    endStage(); // End the stage
    return globalScore >= targetScore; // Check if target score is achieved
}

