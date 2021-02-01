// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _SQUARE_H
#define _SQUARE_H
#include "Piece.h"
#include <iostream>
class Piece;
using namespace std;

/**
 * This class is a representation of each section of the board. Each square has a location and can
 * hold a piece.
 */
class Square {
    public:

        /**
         * This is the constructor for the square
         *
         * @param rank This is the rank position of the piece
         * @param file This is the file position of the piece
         */
        Square(int rank, int file);

        /**
         * This is because the set occupant assumed the the occupant would be a piece, and set
         * the piece location.
         */
        void setOccupantNull();

        /**
         * This gets the rank of the square
         */
        int getRank();
    
        /**
         * This gets the files of the square
         */
        int getFile();
    
        /**
         * This determines if the square has a corresponding piece
         */
        bool isOccupied();
    
        /**
         * This returns the piece on the square
         */
        Piece* getOccupant();

        /**
         * This sets the occupant of the square to a piece
         *
         * @param occupant This is the piece stored in the square
         */
        void setOccupant(Piece* occupant);

        /**
         * This gets the value of the piece on the occupied square
         */
        int getValue();

        /**
         * This overrides
         */
        friend ostream& operator<< (ostream& output, const Square& square);

        /**
         * This determines if a piece can move to the square
         *
         * @param location This is the location of the moved piece
         */
        bool canMoveTo(Square& location);

    private:

        /**
         * This is the rank of the square
         */
        int _rank;

        /**
         * This is the file of the square
         */
        int _file;

        /**
         * This is the occupant of the square
         */
        Piece* _occupant;
};
#endif //_SQUARE_H
