
#ifndef HIGHSCORETABLE_H
#define HIGHSCORETABLE_H

#define HIGHSCORETABLESIZE 10
#include "HighScore.h"
#include <vector>

class HighScoreTable {
public:

    /* Deconstructor */
    ~HighScoreTable();

    /* Stores every high score loaded from the file to the scores vector */
    void loadHighScoreTableFile(std::string name, int score);

    /* Adds the player's name and score to the high scores if the score is in the top 10 */
    void checkScoreBoard(std::string name, int score);

    /* Get the size of the current high score table */
    int getTableSize();

    /* Returns a highscore */
    HighScore* getSpecificHighScore(int index);

    /* Returns a string of the highscore table */
    std::string seeHighScoreTable();

private:
    std::vector<HighScore*> scores;
};

#endif // HIGHSCORETABLE_H