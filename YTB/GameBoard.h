#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Tile.h"
#include <string>

#define MAX_GRID_SIZE 26
#define ADJACENT_ARRAY_SIZE 4

class GameBoard {
public:

    /* Constructor */
    GameBoard();

    /* Deconstructor */
    ~GameBoard();

    /* Returns the points to be added to the player who placed the tile after calculation */
    int getPlayerPoints();

    /* Resets the point calculation system to allow a brand new calculation for the next player */
    void resetIncrementingPoints();

    /* returns QWIRKLEChecker */
    bool getQWIRKLE();

    /* sets QWIRKLEChecker, used for resetting */
    void setQWIRKLE(bool QWIRKLEChecker);

    /* When a player places a tile, tile must be checked if it is a valid placement */
    void placeTileChecker(Tile* tile, char coorLetter, int coorNum);

    /* Places the tile either after it is validated or when it is loading from the savefile*/
    void placeTile(Tile* tile, int rowChosen, int colChosen);

    /* Returns a toString of the whole GameBoard */
    std::string getGameBoardToString(bool colourEnabled);

    /* Contains all functions that checks if the tile is valid */
    void validMove(char tileColour, int tileShape, int rowChosen, int colChosen);

    /* Checks if the coordinate is empty */
    void coorIsEmpty(int rowChosen, int colChosen);

    /* Checks if there is an adjacent tile */
    void tileIsLinked(int rowChosen, int colChosen);

    /* Checks if the diagonal is of either the same shape or colour AND the tile is unique in the diagonal.
    If it is, add a point for every tile in the diagonal */
    void checkTL(int rowChosen, int colChosen, char tileColour, int tileShape);
    void checkTR(int rowChosen, int colChosen, char tileColour, int tileShape);
    void checkBL(int rowChosen, int colChosen, char tileColour, int tileShape);
    void checkBR(int rowChosen, int colChosen, char tileColour, int tileShape);

    /* Throws an exception if either the tile is not same in either the colour or the shape */
    void errorColourShape();

    /* Throws an excepton if tile is not unique in the diagonal */
    void errorSimilarTile();

private:
    Tile* board[MAX_GRID_SIZE][MAX_GRID_SIZE];

    /* A boolean that checks if it is the first tile to be placed on the board */
    bool firstTilePlaced;

    /* A boolean that checks if a player scores a QWIRKLE */
    bool QWIRKLEChecker;

    /* Integers that keep track of the scores of each diagonal where the tile is placed*/
    int incrementingPlayerPointsTL;
    int incrementingPlayerPointsTR;
    int incrementingPlayerPointsBL;
    int incrementingPlayerPointsBR;
};
#endif //GAMEBOARD_H