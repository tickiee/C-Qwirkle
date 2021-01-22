#include "Player.h"

Player::Player(std::string playerNo, std::string playerName) {
    this->playerNo = playerNo;
    this->playerName = playerName;
    this->playerScore = 0;
    this->playerTurn = false;
    playerHand = new LinkedList();
}

Player::~Player() {
    clear();
}

void Player::clear() {
    delete playerHand;
}

std::string Player::getPlayerNo() {
    return this->playerNo;
}

std::string Player::getPlayerName() {
    return this->playerName;
}

int Player::getPlayerScore() {
    return this->playerScore;
}

void Player::setPlayerScore(int score) {
    this->playerScore = playerScore + score;
}

bool Player::getPlayerTurn() {
    return this->playerTurn;
}

void Player::setPlayerTurn(bool playerTurn) {
    this->playerTurn = playerTurn;
}

std::string Player::viewPlayerHand() {
    std::string hand = "";

    for(int i = 0; i < playerHand->getSize(); ++i) {
        hand = hand + playerHand->getTileToString(i) + ",";
    }

    hand = hand.substr(0, (hand.length() - 1));

    return hand;
}

int Player::getPlayerHandSize() {
    return playerHand->getSize();
}

void Player::addTile(Tile* tileAdded) {
    playerHand->addBack(tileAdded);
}

void Player::removeTile(Tile* tileMove) {
    bool boolChecker = false;
    for(int i = 0; i < getPlayerHandSize() && !boolChecker; ++ i) {
        if(getTile(i)->getColour() == tileMove->getColour() && getTile(i)->getShape() == tileMove->getShape()) {
            playerHand->deleteAt(i);
            boolChecker = true;
        }
    }
}

Tile* Player::getTile(int index) {
    return playerHand->getTile(index);
}

std::string Player::playerToString() {
    return playerName + "\n" + std::to_string(playerScore) + "\n" + viewPlayerHand() + "\n";
}