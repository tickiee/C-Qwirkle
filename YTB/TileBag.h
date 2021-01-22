#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"
#include "TileCodes.h"
#include <random>

class TileBag {
public:

    /* Constructor */
    TileBag();

    /* Deconstructor */
    ~TileBag();

    /* Used in deconstructor */
    void clear();

    /* Creates the temporary linkedList */
    void generateTempListTileBag(); //u

    /* Creates the main linkedList */
    void generateTileBag(); //u
    std::string viewTileBag(); //u

    int getTempListTileBagSize();
    int getTileBagSize(); //u

    /* Returns the first Tile in the linkedlist to be added to the player's hand */
    Tile* addTileToPlayerHand();

    /* Adds a tile to the TileBag */
    void addTileToTileBag(Tile* tile);

private:

    /* Generates a temporary linkedlist that contains all the tiles in order */
    LinkedList* tempLinkedList;

    /* Randomizes the Tiles in the temporary linkedlist and stores them in this linkedlist.
    This linkedlist will be the main linkedlist where players take tiles from. */
    LinkedList* tilebagLinkedList;
};

#endif // TILEBAG_H