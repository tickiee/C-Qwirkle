#include "GameEngine.h"

void GameEngine::addPlayer(std::string playerNo, std::string playerName) {
    playerList.push_back(new Player(playerNo, playerName));
}

void GameEngine::startGame() {
    setPlayerTurn(playerList.at(0));
    tileBag = new TileBag();
    tileBagActivity();
    gameboard = new GameBoard();
}

Player* GameEngine::getPlayer(int index) {
    return playerList.at(index);
}

std::string GameEngine::getPlayerName(int index) {
    return getPlayer(index)->getPlayerName();
}

void GameEngine::tileBagActivity() {
    tileBag->generateTempListTileBag();
    tileBag->generateTileBag();
    for(unsigned int i = 0; i < playerList.size(); ++i) {
        for(int j = 0; j < PLAYERHANDSIZE; ++j) {
            playerList.at(i)->addTile(tileBag->addTileToPlayerHand());
        }
    }
}

Player* GameEngine::getCurrentPlayer() {
    Player* player;
    for(unsigned int i = 0; i < playerList.size(); ++i) {
        if(playerList.at(i)->getPlayerTurn()) {
            player = playerList.at(i);
        }
    }

    return player;
}

void GameEngine::currentPlayerPlaceTile(Player* player, char colour, int shape, char coorLetter, int coorNum) {
    Tile* removeTile = new Tile(colour, shape);
    gameboard->setQWIRKLE(false);

    gameboard->placeTileChecker(removeTile, coorLetter, coorNum);
    int points = gameboard->getPlayerPoints();
    player->setPlayerScore(points);
    currentPlayerRemoveTile(player, removeTile);
    if(tileBag->getTileBagSize() > 0) {
        currentPlayerDrawTile(player);
    }
}

bool GameEngine::playerQWIRKLE() {
    return gameboard->getQWIRKLE();
}

void GameEngine::setPlayerScore(Player* player, int score) {
    player->setPlayerScore(score);
}

void GameEngine::currentPlayerReplaceTile(Player* player, char colour, int shape) {
    Tile* replaceTile = new Tile(colour, shape);
    currentPlayerRemoveTile(player, replaceTile);
    tileBag->addTileToTileBag(replaceTile);
    currentPlayerDrawTile(player);
}

bool GameEngine::checkIfTileInPlayerHand(Player* player, char colour, int shape) {
    bool boolChecker = false;

    for(int i = 0; i < player->getPlayerHandSize() && !boolChecker; ++i) {
        if(player->getTile(i)->getColour() == colour && 
            player->getTile(i)->getShape() == shape) {
            boolChecker = true;
        }
    }

    return boolChecker;
}

void GameEngine::currentPlayerRemoveTile(Player* player, Tile* playerTile) {
    player->removeTile(playerTile);
}

void GameEngine::currentPlayerDrawTile(Player* player) {
    player->addTile(tileBag->addTileToPlayerHand());
}

void GameEngine::setPlayerTurn(Player* player) {
    player->setPlayerTurn(true);
}

void GameEngine::nextPlayerTurn(Player* player) {
    player->setPlayerTurn(false);
    for(unsigned int i = 0; i < playerList.size(); ++i) {
        if(playerList.at(i) == player) {
            if(i == (playerList.size() - 1)) {
                playerList.at(0)->setPlayerTurn(true);
            }
            else {
                playerList.at(i + 1)->setPlayerTurn(true);
            }
        }
    }
}

void GameEngine::setPlayerHand(Player* player, std::string loadPlayerHandFromFile) {
    std::replace(loadPlayerHandFromFile.begin(), loadPlayerHandFromFile.end(), ',', ' ');
    std::stringstream ss(loadPlayerHandFromFile);
    std::string eachTile;
    std::vector<std::string> cont;
    while(ss >> eachTile) {
        cont.push_back(eachTile);
    }

    for(unsigned int i = 0; i < cont.size(); ++i) {
        std::string stringTile = cont[i];
        char colour = stringTile[0];
        int shape = std::stoi(stringTile.substr(1, 1));
        Tile* tile = new Tile(colour, shape);
        player->addTile(tile);
    }
}

void GameEngine::setTileBag(std::string loadTileBagFromFile) {
    tileBag = new TileBag();
    std::replace(loadTileBagFromFile.begin(), loadTileBagFromFile.end(), ',', ' ');
    std::stringstream ss(loadTileBagFromFile);
    std::string eachTile;
    std::vector<std::string> cont;
    while(ss >> eachTile) {
        cont.push_back(eachTile);
    }

    for(unsigned int i = 0; i < cont.size(); ++i) {
        std::string stringTile = cont[i];
        char colour = stringTile[0];
        int shape = std::stoi(stringTile.substr(1, 1));
        Tile* tile = new Tile(colour, shape);
        tileBag->addTileToTileBag(tile);
    }
}

void GameEngine::setPlayerTurn(std::string playerName) {
    for(unsigned int i = 0; i < playerList.size(); ++i) {
        if(playerList.at(i)->getPlayerName().compare(playerName) == 0) {
            playerList.at(i)->setPlayerTurn(true);
        }
    }
}

std::string GameEngine::viewCurrentGameScoreBoard() {
    std::string statement = "";
    for(unsigned int i = 0; i < playerList.size(); ++i) {
        statement = statement + "Score for " + playerList.at(i)->getPlayerName() + ": " + 
                    std::to_string(playerList.at(i)->getPlayerScore()) + "\n";
    }

    return statement;
}

std::string GameEngine::viewCurrentPlayerHand() {
    std::string statement;
    
    for(unsigned int i = 0; i < playerList.size(); ++i) {
        if(playerList.at(i)->getPlayerTurn()) {
            statement = playerList.at(i)->viewPlayerHand();
        }
    }
    
    return statement;
}

std::string GameEngine::savingTileBag() {
    std::string colourized = tileBag->viewTileBag();

    std::replace(colourized.begin(), colourized.end(), ',', ' ');
    std::stringstream ss(colourized);
    std::string eachTile;
    std::vector<std::string> cont;
    while(ss >> eachTile) {
        cont.push_back(eachTile);
    }

    std::string statement = "";
    for(unsigned int i = 0; i < cont.size(); ++i) {
        statement = statement + cont[i].substr(11, 2) + ",";
    }

    statement = statement.substr(0, (statement.length() - 1));
    return statement;
}

std::string GameEngine::getGameBoardToString() {
    return gameboard->getGameBoardToString(true);
}

std::string GameEngine::savingGameBoard() {
    return gameboard->getGameBoardToString(false);
}

void GameEngine::createEmptyGameBoard() {
    gameboard = new GameBoard();
}

void GameEngine::loadingGameBoard(std::string unplacedTile, char coorLetter, int coorNum) {
    char colour = unplacedTile[0];
    int shape = std::stoi(unplacedTile.substr(1, (unplacedTile.length() - 1)));
    Tile* tile = new Tile(colour, shape);
    int rowChosen = coorLetter - 'A';
    int colChosen = coorNum;

    gameboard->placeTile(tile, rowChosen, colChosen);
}

std::string GameEngine::getAllPlayersToString() {
    std::string statement = "";
    for(unsigned int i = 0; i < playerList.size(); ++i) {

        std::string colourizedPlayerHand = playerList.at(i)->viewPlayerHand();

        std::replace(colourizedPlayerHand.begin(), colourizedPlayerHand.end(), ',', ' ');
        std::stringstream ss(colourizedPlayerHand);
        std::string eachTile;
        std::vector<std::string> cont;
        while(ss >> eachTile) {
            cont.push_back(eachTile);
        }

        std::string uncolourizedPlayerHand = "";
        for(unsigned int i = 0; i < cont.size(); ++i) {
            uncolourizedPlayerHand = uncolourizedPlayerHand + cont[i].substr(11, 2) + ",";
        }

        uncolourizedPlayerHand = uncolourizedPlayerHand.substr(0, (uncolourizedPlayerHand.length() - 1));

        statement = statement + playerList.at(i)->getPlayerName() + "\n" +
                    std::to_string(playerList.at(i)->getPlayerScore()) + "\n" +
                    uncolourizedPlayerHand + "\n";
    }
    
    return statement;
}

void GameEngine::getHighScoreBoard() {
    table = new HighScoreTable();
    std::string savefilename("highscores.high");
    std::ifstream inFile2;
    inFile2.open(savefilename);

    if(inFile2.good()) {
        while(!inFile2.eof()) {
            std::string line;
            std::getline(inFile2, line);
            if(line.length() != 0) {
                std::stringstream ss(line);
                std::string eachWord;
                std::vector<std::string> cont;
                while(std::getline(ss, eachWord, ':')) {
                    cont.push_back(eachWord);
                }
                table->loadHighScoreTableFile(cont[0], stoi(cont[1]));
            }
        }
    }
    else {
        std::cout << "Error - File Reading error." << std::endl;
    }
}

std::string GameEngine::seeHighScoreBoard() {
    return table->seeHighScoreTable();
}

void GameEngine::saveHighScoreBoard() {
    std::ofstream savefilename("highscores.high");
    std::string statement = "";
    if(savefilename.is_open()) {
        for(int i = 0; i < table->getTableSize(); ++i) {
            statement = table->getSpecificHighScore(i)->getName() + ":" + std::to_string(table->getSpecificHighScore(i)->getScore());
            savefilename << statement + "\n";
            statement = "";
        }
        savefilename.close();
    }
}

void GameEngine::addNewScore(std::string name, int score) {
    table->checkScoreBoard(name, score);
}

std::string GameEngine::playerNameAndScore() {
    std::string statement = "";
    std::string playerName = "";
    int playerScore = -1;
    for(unsigned int i = 0; i < playerList.size(); ++i) {
        playerName = playerList.at(i)->getPlayerName();
        playerScore = playerList.at(i)->getPlayerScore();
        addNewScore(playerName, playerScore);
        statement = statement + "Score for " + playerName + ": " + 
                    std::to_string(playerScore) + "\n";
    }

    return statement;
}

std::string GameEngine::getWinningPlayerName() {
    std::string playerName = "";
    int score = -1;
    for(unsigned int i = 0; i < playerList.size(); ++i) {
        if(score < playerList.at(i)->getPlayerScore()) {
            score = playerList.at(i)->getPlayerScore();
            playerName = playerList.at(i)->getPlayerName();
        }
    }

    return playerName;
}

int GameEngine::getPlayerListSize() {
    return playerList.size();
}

void GameEngine::clearGame() {
    playerList = std::vector<Player*>();
    delete tileBag;
    delete gameboard;
}

void GameEngine::clearMain() {
    delete table;
}