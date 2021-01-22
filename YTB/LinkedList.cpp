#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->transferTemp = nullptr;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::clear() {

    if(getSize() != 0) {

        while(head != nullptr) {
            TileNode* curr = head;
            head = curr->getNextTileNode();
            delete curr;
        }
    }
}

int LinkedList::getSize() {
    int size = 0;

    if(head == nullptr) {
        size = 0;
    }
    else {
        TileNode* curr = head;
        while(curr != nullptr) {
            curr = curr->getNextTileNode();
            size = size + 1;
        }
    }

    return size;
}

Tile* LinkedList::getTile(int index) {
    Tile* tile;
    TileNode* curr = head;
    
    if(index == 0) {
        tile = curr->getTileData();  
    }
    else if(index == (getSize() - 1)) {
        curr = tail;
        tile = tail->getTileData();
    }
    else {
        int count = 0;

        while(count < index) {
            curr = curr->getNextTileNode();
            count = count + 1;
        }

        tile = curr->getTileData();
    }

    return tile;
}

std::string LinkedList::getTileToString(int index) {
    std::string tileToString = "";
    TileNode* curr = head;
    
    if(index == 0) {
        tileToString = curr->getTileDataToString(curr->getTileData());
    }
    else if(index == (getSize() - 1)) {
        curr = tail;
        tileToString = curr->getTileDataToString(curr->getTileData());
    }
    else  {
        int count = 0;

        while(count < index) {
            curr = curr->getNextTileNode();
            count = count + 1;
        }

        tileToString = curr->getTileDataToString(curr->getTileData());
    }

    return tileToString;
}

void LinkedList::addFront(Tile* tileData) {
    TileNode* newTile = new TileNode(tileData, head);
    
    if(tail == nullptr) {
        tail = newTile;
    }

    head = newTile;
}

void LinkedList::addBack(Tile* tileData) {

    TileNode* newTile = new TileNode(tileData, nullptr);

    if(head == nullptr) {
        head = newTile;
    }
    else {
        TileNode* curr = head;
        while(curr->getNextTileNode() != nullptr) {
            curr = curr->getNextTileNode();
        }
        curr->setNextTileNode(newTile);
    }
    tail = newTile;
}

void LinkedList::deleteAt(int index) {
    if(index == 0) {
        deleteFront();
    }
    else if(index == (getSize() - 1)) {
        deleteBack();
    }
    else {
        int count = 0;
        TileNode* curr = head;
        while(count < index) {
            curr = curr->getNextTileNode();
            count = count + 1;
        }
        TileNode* before = head;
        while(before->getNextTileNode() != curr) {
            before = before->getNextTileNode();
        }
        before->setNextTileNode(curr->getNextTileNode());
        delete curr;
    }
}

void LinkedList::deleteFront() {
    if(head != nullptr) {
        TileNode* curr = head;
        head = curr->getNextTileNode();
        delete curr;
    }
}

void LinkedList::deleteBack() {
    TileNode* end = tail;
    if(tail != nullptr) {
        TileNode* curr = head;
        while(curr->getNextTileNode() != tail) {
            curr = curr->getNextTileNode();
        }
        curr->setNextTileNode(nullptr);
        tail = curr;
    }

    delete end;
}

void LinkedList::transferAt(int index, LinkedList* randomList) {

    if(index == 0) {
        transferTemp = transferFront();
    }
    else if(index == (getSize() - 1)) {
        transferTemp = transferBack();
    }
    else {
        int count = 0;
        TileNode* curr = head;
        while(count < index) {
            curr = curr->getNextTileNode();
            count = count + 1;
        }
        TileNode* before = head;
        while(before->getNextTileNode() != curr) {
            before = before->getNextTileNode();
        }
        before->setNextTileNode(curr->getNextTileNode());
        transferTemp = curr->getTileData();
        delete curr;
    }

    char lookColour = transferTemp->getColour();
    int lookShape = transferTemp->getShape();

    delete transferTemp;
    transferTemp = nullptr;

    randomList->addBack(new Tile(lookColour, lookShape));
}

Tile* LinkedList::transferFront() {

    Tile* tileToTransfer = nullptr;

    if(head != nullptr) {
        TileNode* curr = head;
        head = curr->getNextTileNode();
        tileToTransfer = curr->getTileData();
        delete curr;
    }
    return tileToTransfer;
}

Tile* LinkedList::transferBack() {

    Tile* tileToTransfer = nullptr;

    TileNode* end = tail;
    if(tail != nullptr) {
        TileNode* curr = head;
        while(curr->getNextTileNode() != tail) {
            curr = curr->getNextTileNode();
        }
        tileToTransfer = end->getTileData();
        curr->setNextTileNode(nullptr);
        tail = curr;
        delete end;
    }

    return tileToTransfer;
}