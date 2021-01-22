#ifndef MENU_H
#define MENU_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <limits>

#include "GameEngine.h"


class Menu {
public:

    /* Deconstructor */
    ~Menu();

    /* When the game runs */
    void turnOnGame();

    /* Main Menu */
    void printQwirkleMainMenu();

    /* After Player entered a choice in the Main Menu */
    void afterQwirkleMainMenuChoice(std::string mainMenuChoice);

    /* Game Menu */
    void gameMenu();

    /* After Player entered their input in the Game Menu */
    void playerEnterMove(Player* currentPlayer);

    /* Starts a New Game */
    void startNewGame();

    /* Output Display when playing the game */
    void playGame();

    /* Output Display if Tile does not exist */
    void tileDoesNotExist();

    /* Resets std::cin */
    void resetUserInput();

    /* Add player function that takes in user input */
    void addPlayers(std::string playerNo);

    /* Output Display if user enters EOF */
    void eofDisplay();

    /* Function used to split string */
    std::vector<std::string> splittingString(std::string &string, char split);

    /* When the game end */
    void gameEnd();

private:
    GameEngine* ge = new GameEngine();
};

#endif // MENU_H