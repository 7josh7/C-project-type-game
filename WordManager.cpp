#include "WordManager.h"
#include "Stage.h"
#include "MultipleWordsMode.h"
#include "RandomSpeedMode.h"
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

void WordManager::loadWords(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + fileName);
    }
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    if (words.empty()) {
        throw runtime_error("No words loaded from file: " + fileName);
    }
}

string WordManager::selectRandomWord() {
    if (words.empty()) {
        throw std::runtime_error("No words available to select");
    }
    int randomIndex = std::rand() % words.size();
    string selectedWord = words[randomIndex];
    wordAppearTimes[selectedWord] = std::chrono::high_resolution_clock::now();
    return selectedWord;
}

size_t WordManager::getWordCount() const {
    return words.size();
}

auto WordManager::getWordAppearTime(const string& word) const -> decltype(wordAppearTimes.find(word)->second) {
	auto it = wordAppearTimes.find(word);
	if (it != wordAppearTimes.end()) {
    	return it->second;
	} else {
    	throw std::runtime_error("Word not found: " + word);
	}
}

void WordManager::wordMove(string content, int x, int y, int dropSpeed){
    // Set cursor position above the current word position
    ConsoleUtility::setConsoleCursorPosition(x, y - dropSpeed);

    // Erase the previous position of the word
    for(int i = 0; i < content.size(); i++) {
        cout << " ";
    }

    // Set cursor to new position and display the word
    ConsoleUtility::setConsoleCursorPosition(x, y);
    cout << content;
}

void WordManager::wordErase(string content, int x, int y) {
	ConsoleUtility::setConsoleCursorPosition(x, y);
    for(int i = 0; i < content.size(); i++) {
        cout << " ";
    }
}
