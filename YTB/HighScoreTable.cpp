#include "HighScoreTable.h"
#include <iostream>

HighScoreTable::~HighScoreTable() {
    scores = std::vector<HighScore*>();
}

void HighScoreTable::loadHighScoreTableFile(std::string name, int score) {
    HighScore* highScore = new HighScore(name, score);
    scores.push_back(highScore);
}

void HighScoreTable::checkScoreBoard(std::string name, int score) {
    HighScore* highScore = nullptr;
    bool boolChecker = false;
    
    for(unsigned int i = 0; i < scores.size() && !boolChecker; ++i) {
        if(score >= scores.at(i)->getScore()) {
            highScore = new HighScore(name, score);
            std::vector<HighScore*>::iterator itery = scores.begin();
            scores.insert(itery + i, highScore);
            boolChecker = true;
        }
    }

    if(scores.size() > 10) {
        scores.pop_back();
    }

    if(highScore == nullptr) {
        delete highScore;
    }
}

int HighScoreTable::getTableSize() {
    return scores.size();
}

HighScore* HighScoreTable::getSpecificHighScore(int index) {
    return scores.at(index);
}

std::string HighScoreTable::seeHighScoreTable() {
    std::string highScoreTable = "";
    for(unsigned int i = 0; i < scores.size(); ++i) {
        highScoreTable = highScoreTable + std::to_string(i + 1) + ": " + scores.at(i)->getHighScoreToString() + "\n";
    }
    return highScoreTable;
}