#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "Player.h"
#include "TileBag.h"
#include "Tile.h"
#include "HighScoreTable.h"
#include "GameBoard.h"

#define PLAYERHANDSIZE 6

class GameEngine {
public:

    /* Adds a Player to the vector playerList */
    void addPlayer(std::string playerNo, std::string playerName);

    /* Contains functions to call when a New Game starts */
    void startGame();

    /* Return a Player based on its index in the playerList vector */
    Player* getPlayer(int index);

    /* Returns the Player's name based on its index in the playerList vector */
    std::string getPlayerName(int index);

    /* Contains functions to call when for the TileBag*/
    void tileBagActivity();

    /* Returns the Player playing currently */
    Player* getCurrentPlayer();

    /* When a Player places a Tile */
    void currentPlayerPlaceTile(Player* player, char colour, int shape, char coorLetter, int coorNum);

    /* Returns the boolean of QWIRKLE status */
    bool playerQWIRKLE();

    /* Set the score of the Player */
    void setPlayerScore(Player* player, int score);

    /* When a Player replaces a Tile */
    void currentPlayerReplaceTile(Player* player, char colour, int shape);

    /* Returns a boolean true if the Tile exists in the Player's Hand. 
    It will return false if the Tile does not exist */
    bool checkIfTileInPlayerHand(Player* player, char colour, int shape);

    /* Removes the Tile from the Player's hand */
    void currentPlayerRemoveTile(Player* player, Tile* playerTile);

    /* Draws a Tile from the TileBag to the Player's Hand */
    void currentPlayerDrawTile(Player* player);

    /* Set the current Player's turn */
    void setPlayerTurn(Player* player);

    /* Set the next Player's turn */
    void nextPlayerTurn(Player* player);

    /* Read the Hand of the Player from the savefile */
    void setPlayerHand(Player* player, std::string loadPlayerHandFromFile);

    /* Read the TileBag from the savefile */
    void setTileBag(std::string loadTileBagFromFile);

    /* Read the current player's turn from the savefile */
    void setPlayerTurn(std::string playerName);

    /* Returns the score of all players */
    std::string viewCurrentGameScoreBoard();

    /* Returns the Player's Hand */
    std::string viewCurrentPlayerHand();

    /* Returns the TileBag for saving */
    std::string savingTileBag();

    /* Returns the GameBoard during play */
    std::string getGameBoardToString();

    /* Returns the GameBoard for saving */
    std::string savingGameBoard();

    /* Creates a new GameBoard */
    void createEmptyGameBoard();

    /* Loads the GameBoard and Tiles on the GameBoard */
    void loadingGameBoard(std::string unplacedTile, char coorLetter, int coorNum);

    /* Returns a toString() of Players */
    std::string getAllPlayersToString();

    /* Loading HighScores*/
    void getHighScoreBoard();

    /* Display HighScores*/
    std::string seeHighScoreBoard();

    /* Saving HighScores*/
    void saveHighScoreBoard();

    /* Adding HighScore */
    void addNewScore(std::string name, int score);

    /* Returns the Players and their scores when the game ends */
    std::string playerNameAndScore();

    /* Returns the Player's name that won the game */
    std::string getWinningPlayerName();

    /* Returns the size of playerList */
    int getPlayerListSize();
    
    /* Deleting functions */
    void clearGame();
    void clearMain();

private:

    /* A vector storing the list of Players */
    std::vector<Player*> playerList = {};

    /* For TileBag */
    TileBag* tileBag;

    /* For High Scores */
    HighScoreTable* table;

    /* For Board */
    GameBoard* gameboard;
};

#endif // GAMEENGINE_H