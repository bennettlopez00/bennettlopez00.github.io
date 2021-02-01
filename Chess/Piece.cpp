// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Piece.h"
#include "Square.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Board.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <string>
using namespace std;

Piece::Piece(string symbol, string color) {
    _location = nullptr;
    _symbol = symbol;
    _color = color;
}

vector<Square*> Piece::getVerticalSpaces() {
    /**
    * This method is in piece, as opposed to in Board, because instead of basing the single
    * horizontal movement on two squares, this method gets all the horizontal ranges based on
    * the piece itself. For this reason, it made more sense to place it in Piece as it was
    * based more one the piece than the Board itself.
    */
    vector<Square*> moveableSpaces;
    // The four diagonal sides
    Board* board = Board::getInstance();
    int rank = this->getLocation()->getRank();
    int file = this->getLocation()->getFile() + 1;
    bool isDone = false;
    // Get Left Horizontal
    while ((0 < file && file <= 8) && !isDone) {
       // Get all the empty horizontal spaces
       if (!board->getSquareAt(rank, file)->isOccupied()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           file = file + 1;
       }
       // If the last one is a piece of the opposite color
       else if (board->getSquareAt(rank, file)->getOccupant()->getColor() != this->getColor()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           isDone = true;
       }
       else {
           isDone = true;
       }
    }
    // Rest File
    isDone = false;
    file = this->getLocation()->getFile() - 1;
    // Get Right Horizontal
    while ((0 < file && file <= 8) && !isDone) {
       // Get all the empty horizontal spaces
       if (!board->getSquareAt(rank, file)->isOccupied()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           file = file - 1;
       }
       // If the last one is a piece of the opposite color
       else if (board->getSquareAt(rank, file)->getOccupant()->getColor() != this->getColor()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           isDone = true;
       }
       else {
           isDone = true;
       }
    }
    // Reset Rank and File
    isDone = false;
    file = this->getLocation()->getFile();
    rank = this->getLocation()->getRank() + 1;
    // Get Up Vertical
    while ((0 < rank && rank <= 8) && !isDone) {
       // Get all the empty horizontal spaces
       if (!board->getSquareAt(rank, file)->isOccupied()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           rank = rank + 1;
       }
       // If the last one is a piece of the opposite color
       else if (board->getSquareAt(rank, file)->getOccupant()->getColor() != this->getColor()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           isDone = true;
       }
       else {
           isDone = true;
       }
    }
    // Reset Rank
    isDone = false;
    rank = this->getLocation()->getRank() - 1;
    // Get down Vertical
    while ((0 < rank && rank <= 8) && !isDone) {
       // Get all the empty horizontal spaces
       if (!board->getSquareAt(rank, file)->isOccupied()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           rank = rank - 1;
       }
       // If the last one is a piece of the opposite color
       else if (board->getSquareAt(rank, file)->getOccupant()->getColor() != this->getColor()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           isDone = true;
       }
       else {
           isDone = true;
       }
    }
    return moveableSpaces;
}

vector<Square*> Piece::getHorizontalSpaces() {
    vector<Square*> moveableSpaces;
    Board* board = Board::getInstance();
    int rank = this->getLocation()->getRank() + 1;
    int file = this->getLocation()->getFile() - 1;
    bool isDone = false;
    // 0 < Rank < 8, 0 < File < 8
    // Down Left
    while ((0 < rank && rank <= 8) && (0 < file && file <= 8) && !isDone) {
        // Get all the empty diagonal spaces from the piece, as long as it doesn't go off the Board
        if (!board->getSquareAt(rank, file)->isOccupied()) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            rank = rank + 1;
            file = file - 1;
        }
        // If the last square has an opposing piece
        else if (board->getSquareAt(rank, file)->getOccupant()->getColor() != this->getColor()) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            isDone = true;
        }
        else {
            isDone = true;
        }
    }
    // Reset Rank and File to next square
    isDone = false;
    rank = this->getLocation()->getRank() - 1;
    file = this->getLocation()->getFile() + 1;
    // 0 < Rank < 8, 0 < File < 8
    // Down Right
    while ((0 < rank && rank <= 8) && (0 < file && file <= 8) && !isDone) {
        // Get all the empty diagonal spaces from the piece, as long as it doesn't go off the Board
        if (!board->getSquareAt(rank, file)->isOccupied()) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            rank = rank - 1;
            file = file + 1;
        }
        // If the last square has an opposing piece
        else if (board->getSquareAt(rank, file)->getOccupant()->getColor() != this->getColor()) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            isDone = true;
        }
        else {
            isDone = true;
        }
    }
    // Reset Rank and File to next square
    isDone = false;
    rank = this->getLocation()->getRank() - 1;
    file = this->getLocation()->getFile() - 1;
    // 0 < Rank < 8, 0 < File < 8
    // Up Left
    while ((0 < rank && rank <= 8) && (0 < file && file <= 8) && !isDone) {
        // Get all the empty diagonal spaces from the piece, as long as it doesn't go off the Board
        if (!board->getSquareAt(rank, file)->isOccupied()) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            rank = rank - 1;
            file = file - 1;
        }
        // If the last square has an opposing piece
        else if (board->getSquareAt(rank, file)->getOccupant()->getColor() != this->getColor()) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            isDone = true;
        }
        else {
            isDone = true;
        }
    }
    // Reset Rank and File to next square
    isDone = false;
    rank = this->getLocation()->getRank() + 1;
    file = this->getLocation()->getFile() + 1;
    while ((0 < rank && rank <= 8) && (0 < file && file <= 8) && !isDone) {
        // Get all the empty diagonal spaces from the piece, as long as it doesn't go off the Board
        if (!board->getSquareAt(rank, file)->isOccupied()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           rank = rank + 1;
           file = file + 1;
        }
        // If the last square has an opposing piece
        else if (board->getSquareAt(rank, file)->getOccupant()->getColor() != this->getColor()) {
           moveableSpaces.push_back(board->getSquareAt(rank, file));
           isDone = true;
        }
        else {
           isDone = true;
        }
    }
    // A set of the diagonal spaces
    return moveableSpaces;
}

void Piece::setSymbol(string newSymbol) {
    _symbol = newSymbol;
}

void Piece::setColor(string color) {
    _color = color;
}

string Piece::getColor() {
    return _color;
}

Square* Piece::getLocation() {
    return _location;
}

bool Piece::isOnSquare() {
    bool isOccupied = false;
    if (_location != nullptr) {
        isOccupied = true;
    }
    return isOccupied;
}

int Piece::moveTo(Square& location, Player& byPlayer) {
    // 0: No check, 1: Check, 2: Self Check, 3: Wrong Move
    // This method verifies check, and not the previous canMoveTo, due to the fact
    // That in order to check for check, the pieces have to be moved in order to see
    // If either king can be attacked.
    // Check if move is valid
    int isInCheck = 0;
    bool capture = false;
    if (!this->canMoveTo(&location)) {
        isInCheck = 3;
    }
    // If the move is valid
    if (isInCheck != 3) {
        Square* originLocation = _location;
        Piece* originPiece = originLocation->getOccupant();
        Piece* capturedPiece = nullptr;
        // Get the captured Piece
        if (location.getOccupant() != nullptr) {
            capturedPiece = location.getOccupant();
        }
        // Test to see if it's a capture or a move
        if (location.isOccupied()) {
            capture = true;
        }
        location.setOccupant(this);
        originLocation->setOccupantNull();
        // ** Check for Check **
        isInCheck = Board::getInstance()->checkForCheck(&byPlayer, capturedPiece);
        if (isInCheck == 2) {
            // If it causes self check, then move the pieces back
            originLocation->setOccupant(originPiece);
            if (capturedPiece != nullptr) {
                location.setOccupant(capturedPiece);
            }
            else {
                location.setOccupantNull();
            }
        }
        // ...Then complete the move
        else if (isInCheck == 1 || isInCheck == 0) {
            _moved = true;
            if (capture) {
                byPlayer.capture(capturedPiece);
            }
        }
    }
    return isInCheck;
}

bool Piece::hasMoved() {
    return _moved;
}

ostream& operator<< (ostream& output, const Piece& piece) {
    //output << piece._color << piece._symbol;
    output << piece._symbol;
    return output;
}

bool Piece::testForCheck(Square* location) {
    bool canMove;
    int isInCheck = 0;
    Player* opponent = Game::getOpponentOf(Game::getCurrentPlayer());
    Square* originLocation = _location;
    Piece* originPiece = originLocation->getOccupant();
    Piece* capturedPiece = nullptr;
    // Get the captured Piece
    if (location->getOccupant() != nullptr) {
        capturedPiece = location->getOccupant();
    }
    location->setOccupant(this);
    originLocation->setOccupantNull();
    // ** Check for Check **
    if (isInCheck != 3) {
        isInCheck = Board::getInstance()->checkForCheck(opponent, capturedPiece);
    }
    if (isInCheck == 0) {
        canMove = true;
    }
    else {
        canMove = false;
    }
     originLocation->setOccupant(originPiece);
     if (capturedPiece != nullptr) {
         location->setOccupant(capturedPiece);
     }
     else {
         location->setOccupantNull();
     }
     return canMove;
}
