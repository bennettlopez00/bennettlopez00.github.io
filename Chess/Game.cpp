// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Game.h"
#include "Board.h"
#include <iostream>
#include <string>
#include "Square.h"
#include "Piece.h"
#include "Player.h"
#include "King.h"
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;
Player* Game::_player = 0;
set<Piece*>* Game::_blackPieces = 0;
Player* Game::_nextPlayer = 0;
set<Piece*>* Game::_whitePieces = 0;
Board* Game::_board = 0;

void Game::initialize() {
    // This initializes the Instances
    _board = Board::getInstance();
    _whitePieces = _board->getWhitePieces();
    _blackPieces = _board->getBlackPieces();
    // These are the two corresponding kings
    King* whiteKing = (King*)_board->getSquareAt(1, 5)->getOccupant();
    King* blackKing = (King*)_board->getSquareAt(8, 5)->getOccupant();
    // These are the two players to be rotated
    _player = new Player("Player White", whiteKing, _whitePieces);
    _nextPlayer = new Player("Player Black", blackKing, _blackPieces);
    // This displays the initial display
    _board->display();
}

Player* Game::getNextPlayer() {
    // This swaps the _player with _nextPlayer
    Player* tempPlayer;
    tempPlayer = _player;
    _player = _nextPlayer;
    _nextPlayer = tempPlayer;
    return _player;
}

Player* Game::getOpponentOf(Player* inputPlayer) {
    // Swap the _playe with the _nextPlayer based on the input player
    Player* returnPlayer = nullptr;
    Player* playerPtr = inputPlayer;
    if (_player == playerPtr) {
        returnPlayer = _nextPlayer;
    }
    else {
        returnPlayer = _player;
    }
    return returnPlayer;
}

Player* Game::getCurrentPlayer() {
    return _player;
}

void Game::getAIMove() {
    // Checkmate is O(n^3), it's not very smart
    // This method does not care about check and checkmate, because that would be taken care of
    // before the AI move is requested.
    set<Piece*>* pieces = _player->getPieces();
    vector<Piece*> pieceList;
    // Convert the list to a vector to be able to access by index
    for (auto piece : *pieces) {
        pieceList.push_back(piece);
    }
    Piece* randomPiece;
    vector<Square*> movableSpaces;
    bool hasMoved = false;
    int randomInteger;
    int counter;
    // Get a random number in the range of the number of pieces in the player set
    randomInteger = getRandomNumber(pieces->size());
    // Get a random piece out of the possible pieces
    randomPiece = pieceList[randomInteger];
    // Get the possible movements of the piece
    movableSpaces = randomPiece->getMovableSpaces();
    // Make sure there are possible moves
    while (movableSpaces.empty()) {
        randomPiece = pieceList[getRandomNumber(pieces->size())];
        movableSpaces = randomPiece->getMovableSpaces();
    }
    // This loop goes until there is a possible move to be made.
    while (!hasMoved) {
        // Try 5 times to get a space that is movable
        counter = 0;
        while (!hasMoved && counter < 5) {
            int testedPiece = randomPiece->moveTo
                    (*movableSpaces[getRandomNumber(movableSpaces.size())], *_player);
            if (testedPiece == 0 || testedPiece == 1) {
                hasMoved = true;
            }
        }
        // If not, start over with a new piece
        if (!hasMoved) {
            randomPiece = pieceList[getRandomNumber(pieces->size())];
            movableSpaces = randomPiece->getMovableSpaces();
            // Find a piece with possible moves
            while (movableSpaces.empty()) {
                randomPiece = pieceList[getRandomNumber(pieces->size())];
                movableSpaces = randomPiece->getMovableSpaces();
            }
        }
    }
}

int Game::getRandomNumber(int range) {
    srand((unsigned)time(0));
    return (rand() % range);
}
