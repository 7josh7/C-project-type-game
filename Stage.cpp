#include "Stage.h"
#include "MultipleWordsMode.h"
#include "RandomSpeedMode.h"
#include "WordManager.h"
#include "showInstructions.h"
#include "ConsoleUtility.h"
#include "Globals.h"
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <cstdlib>

Stage::Stage(int initialTargetScore, int initialDropSpeed, const std::string& initialFileName)
    : targetScore(initialTargetScore), dropSpeed(initialDropSpeed), fileName(initialFileName) {}

void Stage::playSoundEffect(int frequency, int duration) {
    Beep(frequency, duration);
}

void Stage::setConsoleTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Stage::printModeInfo() const {
    std::cout << "Target Score: " << this->targetScore << std::endl;
    std::cout << "Your Current Score: " << globalScore << std::endl;
    std::cout << "Press Enter to start the game...";
    std::cin.get();
}

void Stage::endStage() {
    system("cls");
    if (globalScore >= targetScore) {
        std::cout << "Time's up!" << std::endl;
        std::cout << "Your final score: " << globalScore << std::endl;
        std::cout << "Congratulations! You have achieved your target score! " << "\\(^v^)/";
        std::cin.get();
    } else {
        std::cout << "Time's up! Game over." << std::endl;
        std::cout << "Your final score: " << globalScore << std::endl;
        std::cin.get();
    }
}

void Stage::wordInitialPlace(int &x, int &y) {
    x = rand() % (SCREEN_WIDTH - 10);
    y = 0;
}

bool Stage::runGame() {
    userInput = "";
    system("cls");

    try {
        words.loadWords(fileName);
    } catch (const std::runtime_error& e) {
        throw;
    }

    wordInitialPlace(x, y);

    content = words.selectRandomWord();
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = startTime + std::chrono::minutes(1);
    auto currentTime = std::chrono::high_resolution_clock::now();

    while (std::chrono::high_resolution_clock::now() < endTime) {
        ConsoleUtility::showInfo(userInput, endTime, targetScore, globalScore);
        words.wordMove(content, x, y);

        if (y < SCREEN_HEIGHT - 1) {
            currentTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - words.getWordAppearTime(content));
            y = duration.count() * dropSpeed;
        } else {
            words.wordErase(content, x, y);
            wordInitialPlace(x, y);
            content = words.selectRandomWord();
            userInput = "";
            globalScore -= 5;
        }

        if (_kbhit()) {
            char input = _getch();
            if (input == '\r' || input == '\n') {
                if (userInput == content) {
                    globalScore += 10;
                    playSoundEffect(500, 100);

                    words.wordErase(content, x, y);
                    wordInitialPlace(x, y);
                    content = words.selectRandomWord();
                    userInput = "";
                } else {
                    userInput = "";
                    globalScore -= 5;
                    playSoundEffect(200, 100);
                }
            } else if (input == '\b' && !userInput.empty()) {
                userInput.pop_back();
            } else {
                userInput += input;
            }
        }
    }
    endStage();
    return globalScore >= targetScore;
}

