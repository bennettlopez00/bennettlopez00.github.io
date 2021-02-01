// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#ifndef _GAME_H
#define _GAME_H

// Forward declaration of Player
#include <set>
class Board;
class Player;
class Piece;
class Player;

using namespace std;
/**
 * This method acts as an opening point for the chess game, starting the game and managing
 * turn rotations.
 */
class Game {
    public:
        static Player* getCurrentPlayer();

        /**
         * This method initializes the class Chess.
         */
        static void initialize();

        /**
         * This method gets the next player turn in the player turn rotation.
         */
        static Player* getNextPlayer();

        /**
         * This method gets the oponent of the given player.
         *
         * @param player This is the opponent player of the class
         */
        static Player* getOpponentOf(Player* player);

        /**
         * This gets a random number within a given range
         *
         * @param range The range of the random number
         */
        static int getRandomNumber(int range);

        /**
         * This gets a random move based on the current player and pieces.
         * I also named it Al Gore, because I thought it was funny; Al-Gore-Rithm
         */
        static void getAIMove();

    private:
        /**
         * This is the static board
         */
        static Board* _board;

        /**
         * This is a collection of the white pieces
         */
        static set<Piece*>* _whitePieces;

        /**
         * This is the collection of the black pieces
         */
        static set<Piece*>* _blackPieces;

        /**
         * This is a reference to the current player
         */
        static Player* _player;

        /**
         * This is a reference to the next player
         */
        static Player* _nextPlayer;
};
#endif //_GAME_H
