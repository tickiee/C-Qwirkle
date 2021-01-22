#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"
#include <iostream>
#include <string>

class Tile {
public:

   /* Constructor */
   Tile(char colour, int shape);

   /* Deconstructor */
   ~Tile();

   /* Used in deconstructor */
   void clear();

   /* Returns the colour of the Tile */
   char getColour();

   /* Returns the shape of the Tile */
   int getShape();

   /* Returns the Tile but in Colours (See TileCode.h for details) */
   std::string colourizeTile(std::string uncolourized, std::string tileColour);

   /* Returns a toString of the Tile */
   std::string tileToString();

private:

   /* The colour of the Tile (See TileCodes.h for details)*/
   char colour;

   /* The shape of the Tile (See TileCodes.h for details)*/
   int shape;
};

#endif // ASSIGN2_TILE_H
