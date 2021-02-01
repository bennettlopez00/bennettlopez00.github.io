// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _KING_H
#define _KING_H
#include "Piece.h"
class Square;
class Player;
#include <string>
#include <iostream>
using namespace std;

/**
 * This class is a subclass of RestrictedPiece, which is a subclass of Piece. This class creates
 * a piece type with unique movements and values.
 */
class King: public Piece {
    public:

        /**
         * This is the constructor for the class King
         *
         * @param symbol This is the symbol representation for King
         * @param color This is the color of the piece
         */
        King(string symbol, string color);


        /**
         * This method determines if the piece can move to a certain location
         *
         * @param location This is the location of the requested moved position
         */
        bool canMoveTo(Square* location);

        /**
         * This returns the movable spaces
         */
        vector<Square*> getMovableSpaces();

    private:
        /**
         * This is the color of the piece
         */
        string _color;
};

#endif //_KING_H
