// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _PLAYER_H
#define _PLAYER_H
#include <string>
#include <set>
#include <vector>
class King;
class Piece;
using namespace std;

/**
 * This class implements the player of the chess game. This player has a collection of Pieces
 * and an assigned color and opponent
 */
class Player {
    public:
        /**
         * This is the constructor for the class Player
         *
         * @param name This is the name of the player
         * @param king This is the king of the player
         * @param pieces These are the pieces for the player
         */
        Player(string name, King* king, set<Piece*>* pieces);

        /**
         * This gets the player name
         */
        string getName();

        /**
         * This gets the King of the Player, to determine if the game is over
         */
        King* getKing();

        /**
         * This gets the pieces of the player
         */
        set<Piece*>* getPieces();

        /**
         * This gets all the pieces that have been captured from the opponent
         *
         * @param piece This is the piece to be captured
         */
        void capture(Piece* piece);

    private:
        /**
         * This removes a piece from the current player
         */
        void losePiece(Piece* piece);

        /**
         * This is the player name
         */
        string _name;

        /**
         * This is the Vector of the pieces
         */
        set<Piece*>* _pieces;

        /**
         * This is the vector of captured pieces
         */
        vector<Piece*> _capturedPieces;

        /**
         * This is the king of the player, used to get color and determine if
         * the game is over
         */
        King* _king;

};

#endif //_PLAYER_H
