// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _PAWN_H
#define _PAWN_H
#include <string>
#include <iostream>
#include "Piece.h"
class Square;

/**
 * This class is a subclass of RestrictedPiece, which is a subclass of Piece. This class creates
 * a piece type with unique movements and values.
 */
class Pawn: public Piece {
    public:
        /**
         * This is the default constructor for Pawn
         *
         * @param symbol This is the symbol representation for Pawn
         * @param color This is the color of the piece
         */
        Pawn(string symbol, string color);

        /**
         * This method determines if the piece can move to a certain location
         *
         * @param This is the requested location to move the piece
         */
        bool canMoveTo(Square* location);

        /**
         * This gets all the movable spaces for the piece
         */
        vector<Square*> getMovableSpaces();
    private:
        /**
         * This sets the delegate for the pawn to a queen
         */
        bool _delegate;
};
#endif //_PAWN_H
