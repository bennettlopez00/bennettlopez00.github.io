// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _PIECE_H
#define _PIECE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Square;
class Player;

/**
 * This class is a super class, acting as a general piece class for more specific pieces.
 */
class Piece {
    public:
        /**
         * This is the constructor for the Piece class
         *
         * @param symbol This is the symbol representation for the piece
         * @param color This is the color representation for the piece
         */
        Piece(string symbol, string color);

        /**
         * This method is a virtual method that gets a boolean can a piece move to a square
         *
         * @param location This is the possible moved location
         */
        virtual bool canMoveTo(Square* location) = 0;

        /**
         * This method returns the moved variable
         */
        bool hasMoved();

        /**
         * This method returns the color of the piece
         */
        string getColor();

        /**
         * This method gets the location of the piece
         */
        Square* getLocation();

        /**
         * This method sets the location of the piece
         *
         * @param location This is the location of the set piece
         */
        void setLocation(Square* location) {
            _location = location;
        }

        /**
         * This method determines if the piece is on a square.
         */
        bool isOnSquare();

        /**
         * This method moves a piece to a location
         *
         * @param location This is the moved location
         * @param byPlayer This is the player moving the piece
         */
        int moveTo(Square& location, Player& byPlayer);

        /**
         * This method sets the color of the piece
         *
         * @param color This is the set color of the piece
         */
        void setColor(string color);

        /**
         * This method overrides the << operator, which cout << returns a representation of Piece.
         *
         * @param output This is the ostream output
         * @param bishop This is the Piece
         */
        friend ostream& operator<< (ostream& output, const Piece& piece);

        /**
         * This sets the pieces hasMoved to true
         */
        void setMoved();

        /**
         * This tests for check, by moving a piece to a location, checking for check, and moving
         * it back. This isn't used in the moveTo when checking for check, because moveTo can either
         * move the piece or not, while this never actually moves the piece
         */
        bool testForCheck(Square* location);

        /**
         * This sets the cout symbol
         */
        void setSymbol(string newSymbol);

        /**
         * This is a pure virtual method for getting the moveable pieces
         */
        virtual vector<Square*> getMovableSpaces() = 0;

        /**
         * This gets the horizontal spaces
         */
        vector<Square*> getHorizontalSpaces();

        /**
         * This gets a vector of vertical spaces
         */
        vector<Square*> getVerticalSpaces();

    private:
        /**
         * This is the color of the piece
         */
        string _color;

        /**
         * This is the location of the piece
         */
        Square *_location;

        /**
         * This is the representative symbol of the piece
         */
        string _symbol;

        /**
         * This is the moved variable
         */
        bool _moved = false;
};
#endif //_PIECE_H
