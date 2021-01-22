#include "HighScore.h"

HighScore::HighScore(std::string name, int score) {
    this->name = name;
    this->score = score;
}

std::string HighScore::getName() {
    return this->name;
}

int HighScore::getScore() {
    return this->score;
}

std::string HighScore::getHighScoreToString() {
    return this->name + " " + std::to_string(this->score);
}