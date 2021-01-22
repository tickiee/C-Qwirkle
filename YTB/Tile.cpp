#include "Tile.h"

Tile::Tile(char colour, int shape) {
    this->colour = colour;
    this->shape = shape;
}

Tile::~Tile() {
    
}

char Tile::getColour() {
    return this->colour;
}

int Tile::getShape() {
    return this->shape;
}

std::string Tile::colourizeTile(std::string uncolourized, std::string tileColour) {
   std::string colouredTile = "";

    if(tileColour.compare("R") == 0) {
        colouredTile = F_RED(uncolourized);
    }
    else if(tileColour.compare("O") == 0) {
        colouredTile = F_ORANGE(uncolourized);
    }
    else if(tileColour.compare("Y") == 0) {
        colouredTile = F_YELLOW(uncolourized);
    }
    else if(tileColour.compare("G") == 0) {
        colouredTile = F_GREEN(uncolourized);
    }
    else if(tileColour.compare("B") == 0) {
        colouredTile = F_BLUE(uncolourized);
    }
    else {
        colouredTile = F_PURPLE(uncolourized);
    }
    
    return colouredTile;
}

std::string Tile::tileToString() {
    std::string colourToString(1, colour);
    std::string shapeToString = std::to_string(shape);
    std::string uncolourize = colourToString + shapeToString;
    std::string colourize = colourizeTile(uncolourize, colourToString);

    return colourize;
}