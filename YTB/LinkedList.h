
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
   
#include "TileNode.h"
#include "Tile.h"

class LinkedList {
public:

    /* Constructor */
    LinkedList();

    /* Deconstructor */
    ~LinkedList();

    /* Used in deconstructor */
    void clear();

    /* Returns the size of the linked list */
    int getSize();

    /* Returns the Tile in the linked list based on the index */
    Tile* getTile(int index);

    /* Returns the toString of the Tile in the linked list based on the index */
    std::string getTileToString(int index);

    /* Adding a tile to the linked list */
    void addFront(Tile* tileData);
    void addBack(Tile* tileData);

    /* Deleteing a tile from the linked list */
    void deleteAt(int index);
    void deleteFront();
    void deleteBack();

    /* Transfering a tile from one linked list to the other */
    void transferAt(int index, LinkedList* randomList);
    Tile* transferFront();
    Tile* transferBack();

private:
   TileNode* head;
   TileNode* tail;

   /* A Tile that is used to define the Tile to be transfered from one linked list to the other */
   Tile* transferTemp;
};

#endif // LINKEDLIST_H