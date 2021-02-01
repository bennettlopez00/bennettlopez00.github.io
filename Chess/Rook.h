// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _ROOK_H
#define _ROOK_H
#include <string>
#include <iostream>
class Square;
class Player;
using namespace std;
#include "Piece.h"

/**
 * This class is a subclass to Piece, which has a unique value, color and move set
 */
class Rook: public Piece {
    public:

        /**
         * This is the constructor for the class Rook
         *
         * @param symbol This is the visual representation of the piece
         * @param color This is the visual representation of the color of the piece
         */
        Rook(string symbol, string color);

        /**
         * This determines if the piece can move to a location
         *
         * @param location This is the permitted moved location
         */
        bool canMoveTo(Square* location);

        /**
         * This method gets the movable spaces of the pieces
         */
        vector<Square*> getMovableSpaces();
};
#endif //_ROOK_H
