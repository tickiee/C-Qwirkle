#include "TileBag.h"

TileBag::TileBag() {
    tempLinkedList = new LinkedList();
    tilebagLinkedList = new LinkedList();
}

TileBag::~TileBag() {
    clear();
}
    
void TileBag::clear() {
    delete tempLinkedList;
    delete tilebagLinkedList;
}

void TileBag::generateTempListTileBag() {

    char colourArr [ARRAYSIZE] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapeArr [ARRAYSIZE] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    for(int repeat = 0; repeat < 2; ++repeat) {
        for(int i = 0; i < ARRAYSIZE; ++i) {
            for(int j = 0; j < ARRAYSIZE; ++j) {
                Tile* newTile = new Tile(colourArr[i], shapeArr[j]);
                tempLinkedList->addBack(newTile);
            }
        }
    }
}

void TileBag::generateTileBag() {

    int min = 0;
    int max = tempLinkedList->getSize();
    int index = -1;
    std::random_device engine;

    for(int i = 0; i < max; ++i) {
        int size = tempLinkedList->getSize() - 1;
        std::uniform_int_distribution<int> uniform_dist(min, size);
        index = uniform_dist(engine);
        tempLinkedList->transferAt(index, tilebagLinkedList);
    }
}

std::string TileBag::viewTileBag() {

    std::string randomListTilesInBag = "";

    for(int i = 0; i < tilebagLinkedList->getSize(); ++i) {
        randomListTilesInBag = randomListTilesInBag + tilebagLinkedList->getTileToString(i) + ",";
    }

    randomListTilesInBag = randomListTilesInBag.substr(0, (randomListTilesInBag.length() - 1));

    return randomListTilesInBag;
}

int TileBag::getTempListTileBagSize() {
    return tempLinkedList->getSize();
}

int TileBag::getTileBagSize() {
    return tilebagLinkedList->getSize();
}

Tile* TileBag::addTileToPlayerHand() {
    Tile* playerTile = nullptr;
    playerTile = tilebagLinkedList->getTile(0);
    tilebagLinkedList->deleteFront();
    
    return playerTile;
}

 void TileBag::addTileToTileBag(Tile* tile) {
    tilebagLinkedList->addBack(tile);
}