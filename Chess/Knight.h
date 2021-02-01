// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _KNIGHT_H
#define _KNIGHT_H
#include "Piece.h"
#include <string>
#include <iostream>

/**
 * This method is a subclass of Piece. This class creates a piece type with unique movements and
 * values.
 */
class Knight: public Piece {
    public:

        /**
         * This is the default constructor for Knight
         *
         * @param symbol This is the symbol representation for Knight
         * @param color This is the color of the piece
         */
        Knight(string symbol, string color);


        /**
         * This determines if a piece can move to a position
         *
         * @location This determines if the piece can move to this location
         */
        bool canMoveTo(Square* location);

        /**
         * This method gets all the movable squares of the piece
         */
        vector<Square*> getMovableSpaces();

};
#endif //_KNIGHT_H
