#include "GameBoard.h"

GameBoard::GameBoard() {
    for(int row = 0; row < MAX_GRID_SIZE; ++row) {
        for(int col = 0; col < MAX_GRID_SIZE; ++col) {
            board[row][col] = nullptr;
        }
    }
    firstTilePlaced = false;
    QWIRKLEChecker = false;
    incrementingPlayerPointsTL = 0;
    incrementingPlayerPointsTR = 0;
    incrementingPlayerPointsBL = 0;
    incrementingPlayerPointsBR = 0;
}

GameBoard::~GameBoard() {
    for(int row = 0; row < MAX_GRID_SIZE; ++row) {
        for(int col = 0; col < MAX_GRID_SIZE; ++col) {
            delete board[row][col];
        }
    }
}

int GameBoard::getPlayerPoints() {
    int incrementingPlayerPoints = 1;
    incrementingPlayerPoints += incrementingPlayerPointsTL + incrementingPlayerPointsTR +
                                    incrementingPlayerPointsBL + incrementingPlayerPointsBR;
    if((incrementingPlayerPointsTL + incrementingPlayerPointsBR) > 0 &&
        (incrementingPlayerPointsTR + incrementingPlayerPointsBL) > 0) {
        ++incrementingPlayerPoints;
    }
    if((incrementingPlayerPointsTR + incrementingPlayerPointsBL) == 5) {
        incrementingPlayerPoints = incrementingPlayerPoints + 6;
        QWIRKLEChecker = true;
    }
    if((incrementingPlayerPointsBR + incrementingPlayerPointsTL) == 5) {
        incrementingPlayerPoints = incrementingPlayerPoints + 6;
        QWIRKLEChecker = true;
    }

    resetIncrementingPoints();
    return incrementingPlayerPoints;
}

void GameBoard::resetIncrementingPoints() {
    incrementingPlayerPointsTL = 0;
    incrementingPlayerPointsTR = 0;
    incrementingPlayerPointsBL = 0;
    incrementingPlayerPointsBR = 0;
}

bool GameBoard::getQWIRKLE() {
    return this->QWIRKLEChecker;
}

void GameBoard::setQWIRKLE(bool QWIRKLEChecker) {
    this->QWIRKLEChecker = QWIRKLEChecker;
}

void GameBoard::placeTileChecker(Tile* tile, char coorLetter, int coorNum) {
    
    char tileColour = tile->getColour();
    int tileShape = tile->getShape();

    int rowChosen = coorLetter - 'A';
    int colChosen = coorNum;
    if(firstTilePlaced) {
        validMove(tileColour, tileShape, rowChosen, colChosen);
    }
    placeTile(tile, rowChosen, colChosen);
}

void GameBoard::placeTile(Tile* tile, int rowChosen, int colChosen) {
    firstTilePlaced = true;
    board[rowChosen][colChosen] = tile;
}

std::string GameBoard::getGameBoardToString(bool colourEnabled) {
    std::string boardString = "";
    boardString.append("      0     2     4     6     8    10    12    14    16    18    20    22    24\n");
    boardString.append("   ----------------------------------------------------------------------------------\n");

    for(int row = 0; row < MAX_GRID_SIZE; ++row) {
        char boardLetter = 'A';
        boardLetter = boardLetter + row;
        std::string boardLetterToString(1, boardLetter);
        if(row % 2 == 0) {
            boardString.append(boardLetterToString);
            boardString.append("  |");
        }
        else {
            boardString.append(boardLetterToString);
            boardString.append("     |");
        }

        for(int col = 0; col < MAX_GRID_SIZE; ++col) {
            if((row + col) % 2 == 0) {
                if(board[row][col] == nullptr) {
                    boardString.append("     |");
                }
                else {
                    boardString.append("  ");
                    if(colourEnabled) {
                        boardString.append(board[row][col]->tileToString());
                    }
                    else {
                        std::string colourToString(1, board[row][col]->getColour());
                        std::string shapeToString = std::to_string(board[row][col]->getShape());
                        std::string uncolourized = colourToString + shapeToString;
                        boardString.append(uncolourized);
                    }
                    boardString.append(" |");
                }
            }
        }

        boardString.append("\n");
    }
    boardString.append("   ----------------------------------------------------------------------------------\n");
    boardString.append("         1     3     5     7     9    11    13    15    17    19    21    23    25");

    return boardString;
}

void GameBoard::validMove(char tileColour, int tileShape, int rowChosen, int colChosen) {
    coorIsEmpty(rowChosen, colChosen);
    tileIsLinked(rowChosen, colChosen);

    checkTL(rowChosen, colChosen, tileColour, tileShape);
    checkTR(rowChosen, colChosen, tileColour, tileShape);
    checkBL(rowChosen, colChosen, tileColour, tileShape);
    checkBR(rowChosen, colChosen, tileColour, tileShape);
}

void GameBoard::coorIsEmpty(int rowChosen, int colChosen) {
    if(board[rowChosen][colChosen] != nullptr) {
        std::string error = "";
        error.append("Error - Invalid tile placement\n");
        error.append("You cannot place a tile above another tile\n");
        error.append("Please place tile at a valid place");
        throw std::runtime_error(error);
    }
}

void GameBoard::tileIsLinked(int rowChosen, int colChosen) {
    bool boolChecker = false;
    int adjacentCol[ADJACENT_ARRAY_SIZE] = {-1, -1, 1, 1};
    int adjacentRow[ADJACENT_ARRAY_SIZE] = {-1, 1, -1, 1};

    for(int i = 0; i < ADJACENT_ARRAY_SIZE && !boolChecker; ++i) {
        int rowChecker = rowChosen + adjacentRow[i];
        int colChecker = colChosen + adjacentCol[i];

        if(rowChecker >= 0 && rowChecker <= 25 &&
            colChecker >= 0 && colChecker <=25 &&
            board[rowChecker][colChecker] != nullptr) {
            boolChecker = true;
        }
    }

    if(!boolChecker) {
        std::string error = "";
        error.append("Error - Invalid tile placement\n");
        error.append("There are no tiles in adjacent\n");
        error.append("Please place tile at a valid place");
        throw std::runtime_error(error);
    }
}

void GameBoard::checkTL(int rowChosen, int colChosen, char tileColour, int tileShape) {
    if(rowChosen > 0 && colChosen > 0) {
        --rowChosen;
        --colChosen;
    }

    while(rowChosen >= 0 && colChosen >= 0 && board[rowChosen][colChosen] != nullptr) {
        if(tileColour != board[rowChosen][colChosen]->getColour() && tileShape != board[rowChosen][colChosen]->getShape()) {
            errorColourShape();
        }
        if(tileColour == board[rowChosen][colChosen]->getColour() &&
            tileShape == board[rowChosen][colChosen]->getShape()) {
            errorSimilarTile();
        }
        ++incrementingPlayerPointsTL;
        --rowChosen;
        --colChosen;
    }
}

void GameBoard::checkTR(int rowChosen, int colChosen, char tileColour, int tileShape) {
    if(rowChosen > 0 && colChosen < 25) {
        --rowChosen;
        ++colChosen;
    }

    while(rowChosen >= 0 && colChosen <= 25 && board[rowChosen][colChosen] != nullptr) {
        if(tileColour != board[rowChosen][colChosen]->getColour() && tileShape != board[rowChosen][colChosen]->getShape()) {
            errorColourShape();
        }
        if(tileColour == board[rowChosen][colChosen]->getColour() &&
            tileShape == board[rowChosen][colChosen]->getShape()) {
            errorSimilarTile();
        }
        ++incrementingPlayerPointsTR;
        --rowChosen;
        ++colChosen;
    }
}

void GameBoard::checkBL(int rowChosen, int colChosen, char tileColour, int tileShape) {
    if(rowChosen < 25 && colChosen > 0) {
        ++rowChosen;
        --colChosen;
    }

    while(rowChosen <= 25 && colChosen >= 0 && board[rowChosen][colChosen] != nullptr) {
        if(tileColour != board[rowChosen][colChosen]->getColour() && tileShape != board[rowChosen][colChosen]->getShape()) {
            errorColourShape();
        }
        if(tileColour == board[rowChosen][colChosen]->getColour() &&
            tileShape == board[rowChosen][colChosen]->getShape()) {
            errorSimilarTile();
        }
        ++incrementingPlayerPointsBL;
        ++rowChosen;
        --colChosen;
    }
}

void GameBoard::checkBR(int rowChosen, int colChosen, char tileColour, int tileShape) {
    if(rowChosen < 25 && colChosen < 25) {
        ++rowChosen;
        ++colChosen;
    }

    while(rowChosen <= 25 && colChosen <= 25 && board[rowChosen][colChosen] != nullptr) {
        if(tileColour != board[rowChosen][colChosen]->getColour() && tileShape != board[rowChosen][colChosen]->getShape()) {
            errorColourShape();
        }
        if(tileColour == board[rowChosen][colChosen]->getColour() &&
            tileShape == board[rowChosen][colChosen]->getShape()) {
            errorSimilarTile();
        }
        ++incrementingPlayerPointsBR;
        ++rowChosen;
        ++colChosen;
    }
}

void GameBoard::errorColourShape() {
    resetIncrementingPoints();
    std::string error = "";
    error.append("Error - Invalid tile placement\n");
    error.append("Tile is not the same colour or shape in the diagonal\n");
    error.append("Please place tile at a valid place");
    throw std::runtime_error(error);
}

void GameBoard::errorSimilarTile() {
    resetIncrementingPoints();
    std::string error = "";
    error.append("Error - Invalid tile placement\n");
    error.append("Tile already exists in the diagonal\n");
    error.append("Please place tile at a valid place");
    throw std::runtime_error(error);
}