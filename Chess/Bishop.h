// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _BISHOP_H
#define _BISHOP_H
#include <string>
#include <iostream>
#include "Piece.h"

/**
 * This class is a subclass of Piece, which is an object held in GameBoard.
 * Each piece has it's own value and move set.
 */
class Bishop: public Piece {
    public:

        /**
         * This is the default constructor for the class Bishop
         *
         * @param symbol This is the symbol for displaying the piece
         * @param color This is the symbol for color when displaying the piece
         */
        Bishop(string symbol, string color);

        /**
         * This method determines if if can move to the specified square.
         *
         * @param location This is the Square that the piece can move to
         */
        bool canMoveTo(Square* location);

        /**
         * This method returns all the moveable spaces
         */
        vector<Square*> getMovableSpaces();
};
#endif
