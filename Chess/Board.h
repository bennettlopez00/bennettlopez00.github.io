// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _BOARD_H
#define _BOARD_H
#include <ostream>
#include <vector>
#include <set>
class Player;

// Included class types
class Piece;
class Square;
using namespace std;

/**
 * This class is the Board for the game. It holds the squares and pieces that make up the gameplay.
 * This class uses a singleton patter for calling the constructor. This class also needs to call
 * the destructor in order to clear the memory of the program.
 */
class Board {
    public:
        /**
         * This is the default destructor for the Board class. This method needs to be called
         * in the implementing class, in order to clear the memory.
         */
        ~Board();

        /**
         * This method returns the instance of the class. This is required by the singleton pattern.
         */
        static Board* getInstance();

        /**
         * This method returns the square at the specified location.
         *
         * @param rank This is the rank of the requested square
         * @param file This is the file of the requested piece
         */
        Square* getSquareAt(int rank, int file);

        /**
         * This method displays the current state of the board.
         */
        void display();

        /**
         * This method implements queen-side Castling
         */
        bool canQueenSideCastle(Player* player);

        /**
         * This move implements king-side castling
         */
        bool canKingSideCastle(Player* player);

        /**
         * This method checks for checkmate
         */
        bool checkForCheckmate();

        /**
         * This method gets all the white spaces in a set
         */
        set<Piece*>* getWhitePieces();

        /**
         * This method gets all the black pieces in a set
         */
        set<Piece*>* getBlackPieces();

        /**
         * This method checks for check, not checkmate
         */
        int checkForCheck(Player* player, Piece* removedPiece);

    private:
        vector<Square*> getAttackingPath(Piece* attackingPiece);
        /**
         * This is the private constructor for the class Board
         */
        Board();

        /**
         * This method places the piece on the board.
         *
         * @param addedPiece This is the piece to be placed on the Board
         * @param rank This is the rank of the placed piece
         * @param column This is the column of the placed piece
         */
        void placePiece(Piece* addedPiece, int rank, int column);

        /**
         * This is the L/W of the board
         */
        int DIMENSION = 8;

        /**
         * This is the instance of the board
         */
        static Board* _instance;

        /**
         * This is the vector that holds the squares on the board (See getSquareAt())
         */
        vector<Square*> _squares;

        /**
         * This method is a collection of white pieces
         */
        set<Piece*> _boardWhitePieces;

        /**
         * This is a collection of black pieces
         */
        set<Piece*> _boardBlackPieces;

        /**
         * This is a collection of the total pieces
         */
        set<Piece*> _totalPieces;

};
#endif //_BOARD_H
