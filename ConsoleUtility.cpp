#include "ConsoleUtility.h"
#include "Stage.h"
#include "MultipleWordsMode.h"
#include "RandomSpeedMode.h"
#include "WordManager.h"
#include "showInstructions.h"
#include "Globals.h"


void ConsoleUtility::setConsoleCursorPosition(int x, int y) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ConsoleUtility::drawBottomLine() {
    setConsoleCursorPosition(0, 25);
    for (int i = 0; i < 80; ++i) {
        std::cout << "-";
    }
}

void ConsoleUtility::showInfo(const std::string& userInput, std::chrono::time_point<std::chrono::high_resolution_clock> endTime, int targetScore, int globalScore) {
    drawBottomLine();
    setConsoleCursorPosition(0, 26);
    std::cout << "Your input: " << userInput << "                                                ";
    setConsoleCursorPosition(0, 28);    
    auto remainingTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - std::chrono::high_resolution_clock::now());
    std::cout << "Time remaining: " << remainingTime.count() << " seconds" << "  |  ";
    std::cout << "Score: " << globalScore << " (Target:" << targetScore << ")" << std::endl;
}

