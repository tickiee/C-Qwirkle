#include "Menu.h"

Menu::~Menu() {
    
}

void Menu::turnOnGame() {
    ge->getHighScoreBoard();
    printQwirkleMainMenu();
}

void Menu::printQwirkleMainMenu() {

    std::string mainMenuChoice = "";

    std::cout << std::endl;
    std::cout << "=====Qwirkle Main Menu=====" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. View Highscores" << std::endl;
    std::cout << "4. Show Student Information" << std::endl;
    std::cout << "5. Quit" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter choice: " << std::endl;
    std::cout << std::endl;
    
    std::cin >> mainMenuChoice;
    if(!std::cin.eof()) {
        afterQwirkleMainMenuChoice(mainMenuChoice);
    }
    else {
        eofDisplay();
    }
}

void Menu::afterQwirkleMainMenuChoice(std::string mainMenuChoice) {
    if(mainMenuChoice.compare("1") == 0) {
        std::cout << std::endl;
        std::cout << "Starting a New Game" << std::endl;

        std::cout << std::endl;
        std::cout << "Enter the number of players: " << std::endl;
        std::cout << "Minimum 2 Players" << std::endl;
        std::cout << "Minimum 4 Players" << std::endl;

        std::string numberOfPlayer = "";
        std::cin >> numberOfPlayer;

        std::regex regexNoOfPlayersChecker("[2-4]");

        if(!std::cin.eof()) {
            if(std::regex_match(numberOfPlayer, regexNoOfPlayersChecker)) {
                for(int i = 0; i < std::stoi(numberOfPlayer); ++i) {
                    addPlayers(std::to_string(i + 1));  
                }

                resetUserInput();
                startNewGame();
            }
            else {
                std::cout << "Error - Number of Players error" << std::endl;
                std::cout << "Please enter a valid input" << std::endl;
                std::cout << std::endl;
                std::cout << "--- Tip: Type -help for commands ---" << std::endl;

                printQwirkleMainMenu();
            }
        }
        else {
            eofDisplay();
        }
    }
    else if(mainMenuChoice.compare("2") == 0) {
        std::cout << std::endl;
        std::cout << "Load Game" << std::endl;

        std::cout << "Enter the filename from which to load a game" << std::endl;
        
        std::string savefilename;
        std::cin >> savefilename;
        std::string savefile(savefilename + ".save");
    
        std::string countLine;
        std::ifstream countLineFile;
        int numberOfLines = 0;

        countLineFile.open(savefile);

        if(!std::cin.eof()) {
            while(std::getline(countLineFile, countLine)) {
                ++numberOfLines;
            }

            int playerGeneratedLines = numberOfLines - 32;

            std::ifstream inFile;
            inFile.open(savefile);

            countLineFile.close();
            bool fileLoaded = false;

            if(inFile.good()) {
                ge->createEmptyGameBoard();
                int lineIndex = 1;
                while(!inFile.eof()) {
                    std::string line;
                    std::getline(inFile, line);
                    if(line.length() == 0 && lineIndex == 1) {
                        std::cout << "Error - File Reading error." << std::endl;
                        std::cout << "Game could not be loaded" << std::endl;
                    }
                    else {
                        if(lineIndex <= playerGeneratedLines) {
                            if(lineIndex % 3 == 1) {
                                int playerNo = (lineIndex + 2) / 3;
                                ge->addPlayer(std::to_string(playerNo), line);
                            }
                            else if(lineIndex % 3 == 2) {
                                int playerNo = (lineIndex + 1) / 3;
                                int playerNoIndex = playerNo - 1;
                                ge->setPlayerScore(ge->getPlayer(playerNoIndex), std::stoi(line));
                            }
                            else if(lineIndex % 3 == 0) {
                                int playerNo = lineIndex / 3;
                                int playerNoIndex = playerNo - 1;
                                ge->setPlayerHand(ge->getPlayer(playerNoIndex), line);
                            }
                        }
                        else if(lineIndex > playerGeneratedLines && lineIndex < (numberOfLines - 1)) {
                            char letter = line[0];
                            if(letter >= 65 && letter <=90) {
                                std::string boardline = "";
                                int value = -1;
                                if(letter % 2 == 1) {
                                    boardline = line.substr(4, (line.length() - 3));
                                    value = 0;
                                }
                                else {
                                    boardline = line.substr(7, (line.length() - 6));
                                    value = 1;
                                }
                                std::vector<std::string>stringSplit;
                                stringSplit = splittingString(boardline, '|');
                                for(unsigned int i = 0 ; i < stringSplit.size(); ++i) {
                                    if(stringSplit[i] != "     ") {
                                        int col = value + i * 2;
                                        std::string unplacedTile = stringSplit[i].substr(2, 2);
                                        ge->loadingGameBoard(unplacedTile, letter, col);
                                    }
                                }
                            }
                        }
                        else if(lineIndex == (numberOfLines - 1)) {
                            ge->setTileBag(line);
                        }
                        else if(lineIndex == numberOfLines) {
                            ge->setPlayerTurn(line);
                            fileLoaded = true;
                        }
                        ++lineIndex;
                    }
                }
                
                std::cout << "Qwirkle game successfully loaded" << std::endl;
            }
            else {
                std::cout << "Error - File Reading error." << std::endl;
                std::cout << "Game could not be loaded" << std::endl;

                printQwirkleMainMenu();
            }

            inFile.close();

            if(fileLoaded) {
                resetUserInput();
                playGame();
            }
        }
        else {
            eofDisplay();
        }
    }
    else if(mainMenuChoice.compare("3") == 0) {
        std::cout << std::endl;

        std::cout << "View Highscores:" << std::endl;
        std::cout << ge->seeHighScoreBoard() << std::endl;
        std::cout << std::endl;

        printQwirkleMainMenu();
    }
    else if(mainMenuChoice.compare("4") == 0) {
        std::cout << std::endl;
        std::cout << "Show Student Information" << std::endl;

        std::cout << std::endl;
        std::cout << "Name: Rico Wu" << std::endl;
        std::cout << "Student ID: S3769980" << std::endl;
        std::cout << "Email: S3769980@student.rmit.edu.au" << std::endl;

        std::cout << std::endl;
        std::cout << "Name: Merhawi Minassi" << std::endl;
        std::cout << "Student ID: S3668396" << std::endl;
        std::cout << "Email: S3668396@student.rmit.edu.au" << std::endl;

        std::cout << std::endl;
        std::cout << "Name: Jialun Darren Huang" << std::endl;
        std::cout << "Student ID: S3755729" << std::endl;
        std::cout << "Email: S3755729@student.rmit.edu.au" << std::endl;

        std::cout << std::endl;
        std::cout << "Name: Siddhartha Raju Chandra" << std::endl;
        std::cout << "Student ID: S3731026" << std::endl;
        std::cout << "S3731026@student.rmit.edu.au" << std::endl;

        printQwirkleMainMenu();
    }
    else if(mainMenuChoice.compare("5") == 0) {
        std::cout << std::endl;
        
        std::cout << "Quit" << std::endl;

        std::cout << std::endl;

        ge->saveHighScoreBoard();

        std::cout << "Thanks for playing!" << std::endl;
        std::cout << "Goodbye." << std::endl;

        ge->clearMain();
        delete ge;

        std::cout << std::endl;
    }
    else if(mainMenuChoice.compare("UUDDLRLRBA") == 0) {
        std::cout << std::endl;
        std::cout << "Enter Hack number: " << std::endl;
        std::cout << "Current Hacks: " << std::endl;
        std::cout << "1. Add new highscore" << std::endl;
        std::string testNumber;
        std::cin >> testNumber;
        if(!std::cin.eof()) {
            if(testNumber.compare("1") == 0) {
                std::string name = "";
                int score = -1;
                std::cout << "Enter name: " << std::endl;
                std::cin >> name;
                std::cout << "Enter score: " << std::endl;
                std::cin >> score; 
                ge->addNewScore(name, score);
            }
            else {
                std::cout << "Hack does not exist" << std::endl;
            }
            std::cout << std::endl;
            std::cout << "Rest in peace." << std::endl;
            printQwirkleMainMenu();
        }
        else {
            eofDisplay();
        }
    }
    else if(mainMenuChoice.compare("-help") == 0) {
        std::cout << std::endl;

        std::cout << "==========HELP==========" << std::endl;
        std::cout << "Want to play a new game?" << std::endl;
        std::cout << "Enter '1' to create a new game!" << std::endl;

        std::cout << std::endl;

        std::cout << "Want to continue a game?" << std::endl;
        std::cout << "Enter '2' to load your game!" << std::endl;

        std::cout << std::endl;

        std::cout << "Want to view the top scores of the game?" << std::endl;
        std::cout << "Enter '3' to view!" << std::endl;

        std::cout << std::endl;

        std::cout << "Want to see who made the game?" << std::endl;
        std::cout << "Enter '4' to view the developers of the game" << std::endl;

        std::cout << std::endl;

        std::cout << "Enter '5' to Quit the game =(" << std::endl;

        std::cout << std::endl;

        printQwirkleMainMenu();
    }
    else {
        std::cout << std::endl;

        std::cout << "Error - user input." << std::endl;
        std::cout << "Please enter a valid input" << std::endl;
        std::cout << std::endl;
        std::cout << "--- Tip: Type -help for commands ---" << std::endl;

        resetUserInput();

        printQwirkleMainMenu();
    }
}

void Menu::playerEnterMove(Player* currentPlayer) {
    std::cout << "Enter move: " << std::endl;
    std::string move;
    std::getline(std::cin, move);
    if(!std::cin.eof()) {
        if(move.compare("quit") == 0) {
            ge->clearGame();
            printQwirkleMainMenu();
        }
        else if(move.compare("-help") == 0) {
            std::cout << std::endl;

            std::cout << "==========HELP==========" << std::endl;
            std::cout << "Each player can only place a tile at a turn" << std::endl;
            std::cout << "The first player can place his tile at anywhere on the board" << std::endl;
            std::cout << "Following that, all players must place a tile adjacent to any tiles on the board" << std::endl;
            std::cout << "You can only place a tile that has either the same shape or colour as all the tiles in the diagonal" << std::endl;

            std::cout << std::endl;

            std::cout << "Enter 'place [TILE] at [COORDINATE]'" << std::endl;
            std::cout << "[TILE] is the tile on your hand" << std::endl;
            std::cout << "[COORDINATE] is referenced as <row><column>" << std::endl;

            std::cout << std::endl;

            std::cout << "You can replace a tile if you want to or if you are out of moves" << std::endl;
            std::cout << "Enter 'replace [TILE]'" << std::endl;
            std::cout << "[TILE] is the tile on your hand" << std::endl;

            std::cout << std::endl;

            std::cout << "Want to save game?" << std::endl;
            std::cout << "Enter 'save [TEXTFILE]'" << std::endl;
            std::cout << "[TEXTFILE] is the filename (with no spaces)" << std::endl;

            std::cout << std::endl;

            std::cout << "Want to quit game?" << std::endl;
            std::cout << "Enter 'quit'" << std::endl;

            std::cout << std::endl;

            playerEnterMove(currentPlayer);
            playGame();
        }
        else {
            std::regex regexSaveGameChecker("save [a-zA-Z0-9]+");
            std::regex regexPlaceChecker("place [ROYGBP][1-6] at [A-Z]([0-9]|1[0-9]|2[0-5])");
            std::regex regexReplaceChecker("replace [ROYGBP][1-6]");
            
            if(std::regex_match(move, regexSaveGameChecker)) {
                std::string savefilename = move.substr(5, (move.length() - 5));
                std::ofstream savefile(savefilename + ".save");
                if(savefile.is_open()) {
                    savefile << ge->getAllPlayersToString();
                    savefile << ge->savingGameBoard() << std::endl;
                    savefile << ge->savingTileBag() << std::endl;
                    savefile << ge->getCurrentPlayer()->getPlayerName();
                    savefile.close();
                    std::cout << "Game successfully saved" << std::endl;
                }

                playerEnterMove(currentPlayer);
            }
            else if(std::regex_match(move, regexPlaceChecker)) {
                std::string tileChosen = move.substr(6,2);
                char colourTileChosen = tileChosen[0];
                int shapeTileChosen = std::stoi(tileChosen.substr(1,1));

                if(ge->checkIfTileInPlayerHand(currentPlayer, colourTileChosen, shapeTileChosen)) {
                    std::string coorChosen = move.substr(12, (move.length() - 11));
                    char coorLetterChosen = coorChosen[0];
                    int coorNumChosen = std::stoi(coorChosen.substr(1, (coorChosen.length() - 1)));
                    if((coorLetterChosen + coorNumChosen) % 2 == 0) {
                        std::cout << "Error - Invalid Coordinate" << std::endl;
                        std::cout << "Please enter a valid input" << std::endl;
                        std::cout << std::endl;
                        std::cout << "--- Tip: Type -help for commands ---" << std::endl;

                        std::cout << std::endl;
                        playerEnterMove(currentPlayer);
                    }
                    else {
                        try {
                            ge->currentPlayerPlaceTile(currentPlayer, colourTileChosen, shapeTileChosen,
                                                    coorLetterChosen, coorNumChosen);
                        }
                        catch (std::runtime_error& error) {
                            std::cout << "Error - " << error.what() << std::endl;

                            std::cout << std::endl;
                            playerEnterMove(currentPlayer);
                        }
                        if(ge->playerQWIRKLE()) {
                            std::cout << "QWIRKLE" << std::endl;
                        }
                        if(currentPlayer->getPlayerHandSize() == 0) {
                            gameEnd();
                        }
                        else {
                            ge->nextPlayerTurn(currentPlayer);
                            
                            std::cout << std::endl;
                            playGame();
                        }
                    }
                }
                else {
                    tileDoesNotExist();

                    std::cout << std::endl;
                    playerEnterMove(currentPlayer);
                }
            }
            else if(std::regex_match(move, regexReplaceChecker)) {
                std::string tileChosen = move.substr(8,2);
                char colourTileChosen = tileChosen[0];
                int shapeTileChosen = std::stoi(tileChosen.substr(1,1));
                if(ge->checkIfTileInPlayerHand(currentPlayer, colourTileChosen, shapeTileChosen)) {
                    ge->currentPlayerReplaceTile(currentPlayer, colourTileChosen, shapeTileChosen);
                    ge->nextPlayerTurn(currentPlayer);
                    
                    std::cout << std::endl;
                    playGame();
                }
                else {
                    tileDoesNotExist();

                    std::cout << std::endl;
                    playerEnterMove(currentPlayer);
                }
            }
            else {
                std::cout << "Error - user input." << std::endl;
                std::cout << "Please enter a valid input" << std::endl;
                std::cout << std::endl;
                std::cout << "--- Tip: Type -help for commands ---" << std::endl;

                playerEnterMove(currentPlayer);
            }
        }
    }
    else {
        eofDisplay();
    }
}

void Menu::startNewGame() {
    ge->startGame();
    playGame();
}

void Menu::playGame() {
    Player* currentPlayer = ge->getCurrentPlayer();
    std::cout << currentPlayer->getPlayerName() << ", it's your turn" << std::endl;
    std::cout << ge->viewCurrentGameScoreBoard() << std::endl;
    std::cout << ge->getGameBoardToString() << std::endl;
    std::cout << "Your hand is" << std::endl;
    std::cout << ge->viewCurrentPlayerHand() << std::endl;

    playerEnterMove(currentPlayer);
}

void Menu::addPlayers(std::string playerNo) {

    std::cout << "Enter a name for player " << playerNo << " (uppercase characters only)" << std::endl;
    std::string playerName = "";
    std::regex regexChecker("[A-Z]+");
    std::cin >> playerName;
    if(!std::cin.eof()) {
        if(std::regex_match(playerName, regexChecker)){
            int size = ge->getPlayerListSize();
            bool boolChecker = false;

            for(int i = 0; i < size && !boolChecker; ++i) {
                if(ge->getPlayerName(i).compare(playerName) == 0) {
                    boolChecker = true;
                    std::cout << std::endl;
                    std::cout << "Error - Invalid name" << std::endl;
                    std::cout << "Player name is not unique" << std::endl;
                    std::cout << "Please enter a unique name" << std::endl;
                    std::cout << std::endl;

                }
            }
            if(boolChecker) {
                addPlayers(playerNo);
            }
            else {
                ge->addPlayer(playerNo, playerName);
            }
        }
        else {
            std::cout << std::endl;
            std::cout << "Error - Invalid name" << std::endl;
            std::cout << "Please enter a name in all uppercase characters" << std::endl;
            std::cout << std::endl;

            addPlayers(playerNo);
        }
    }
    else {
        eofDisplay();
    }
}

void Menu::tileDoesNotExist() {
    std::cout << "Error - Tile does not exist" << std::endl;
    std::cout << "Please enter a valid input" << std::endl;
    std::cout << std::endl;
    std::cout << "--- Tip: Type -help for commands ---" << std::endl;
}

void Menu::resetUserInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::eofDisplay() {
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;
    std::cout << std::endl;
}

std::vector<std::string> Menu::splittingString(std::string &string, char split) {
    std::stringstream stringStream(string);
    std::string cont;
    std::vector<std::string> container;
    while (std::getline(stringStream, cont, split)) {
        container.push_back(cont);
    }

    return container;
}

void Menu::gameEnd() {
    std::cout << std::endl;
    std::cout << "Game over" << std::endl;
    std::cout << ge->playerNameAndScore() << std::endl;
    std::cout << "Player " << ge->getWinningPlayerName() << " won!" << std::endl;
    
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;
    printQwirkleMainMenu();
}
