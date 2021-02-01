// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _QUEEN_H
#define _QUEEN_H
#include <iostream>
#include <string>
#include "Piece.h"

/**
 * This class is a subclass to Piece, which has a unique value, color and move set
 */
class Queen: public Piece {
    public:

        /**
         * This is the constructor for Queen
         *
         * @param symbol This is the symbol representation for Queen
         * @param color This is the color of the piece
         */
        Queen(string symbol, string color);

        /**
         * This determines if the move can move to a square
         *
         * @location This determines if the piece can move to this location
         */
        bool canMoveTo(Square* location);

        /**
         * This method gets the possible movable spaces of the peice
         */
        vector<Square*> getMovableSpaces();
};

#endif //_QUEEN_H
