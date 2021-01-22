#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

#include "LinkedList.h"

class Player {
public:

    /* Constructor */
    Player(std::string playerNo, std::string playerName);

    /* Deconstructor */
    ~Player();

    /* Used in deconstructor */
    void clear();

    /* Return the player's number */
    std::string getPlayerNo();

    /* Return the player's name */
    std::string getPlayerName();

    /* Return the player's score */
    int getPlayerScore();

    /* Sets the player's score, used to add score to the player */
    void setPlayerScore(int playerScore);

    /* Returns the player's turn status.
    If true, it is the player's turn, else it is not the player's turn. */
    bool getPlayerTurn();

    /* Sets the player's turn status */
    void setPlayerTurn(bool playerTurn);

    /* Returns the list of the player's hand */
    std::string viewPlayerHand();

    /* Returns the number of tiles in the player's hand */
    int getPlayerHandSize();

    /* Add a tile to the player's hand */
    void addTile(Tile* tileAdded);

    /* Removes a tile from the player's hand */
    void removeTile(Tile* tileMove);

    /* Returns a tile that is on the player's hand */
    Tile* getTile(int index);

    /* Returns the name, score and hand of the player */
    std::string playerToString();

private:
    std::string playerNo;
    std::string playerName;
    int playerScore;

    /* Player turn status.
    True = Player's turn, False = Not Player's turn */
    bool playerTurn;

    /* Tiles that are in the Player's hand */
    LinkedList* playerHand;
};

#endif // PLAYER_H