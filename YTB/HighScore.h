#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>

class HighScore {
public:
    
    /* Constructor */
    HighScore(std::string name, int score);

    /* Returns the name of the player */
    std::string getName();

    /* Returns the score of the player */
    int getScore();

    /* Returns a toString of a highscore */
    std::string getHighScoreToString();

private:
    std::string name;
    int score;
};

#endif // HIGHSCORE_H