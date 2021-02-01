// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "King.h"
#include "Pawn.h"
#include "Square.h"
#include "Board.h"
#include "Piece.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

King::King(string symbol, string color): Piece(symbol, color) {}

bool King::canMoveTo(Square* location) {
    bool canMove = false;
    // Set of valid moves in the square
    vector<Square*> moveableSpaces;
    // Getting all Possible square movements
    moveableSpaces = this->getMovableSpaces();
    // Testing to see if the requested move is an available move
    for(int i = 0; i < moveableSpaces.size(); i++) {
        if (moveableSpaces[i] == location) {
            canMove = true;
        }
    }
    // Confirm that the end piece isn't a similar color piece
    if (location->getOccupant() != nullptr && location->getOccupant()->getColor() ==
            this->getColor()) {
        canMove = false;
    }
    return canMove;
}

vector<Square*> King::getMovableSpaces() {
    /**
     * ** NOTE **
     * This gets the possible movements for the King. This repeats some of the logic in king
     * canMoveTo, but instead of returning a boolean, it returns a list of the possible squares.
     * This could have been combined into one method, but that would require repeated logic
     * of determining if a move was in the possible moves, so to make the code more readable, and
     * to avoid scattered repeated logic, the methods are divided up.
     */
    vector<Square*> moveableSpaces;
    // Rank and File of the current Knight Piece
    int file = this->getLocation()->getFile();
    int rank = this->getLocation()->getRank();
    Board* board = Board::getInstance();
    // Getting all Possible square movements
    // Rank + 1, File
    if ((0 < rank + 1 && rank + 1 <= 8) && (0 < file && file <= 8)) {
        if (!(board->getSquareAt(rank + 1, file)->getOccupant() != nullptr && board->
                getSquareAt(rank + 1, file)->getOccupant()->getColor() == this->getColor())) {
            moveableSpaces.push_back(board->getSquareAt(rank + 1, file));
        }
    }
    // Rank + 1, File - 1
    if ((0 < rank + 1 && rank + 1 <= 8) && (0 < file - 1 && file - 1 <= 8)) {
        if (!(board->getSquareAt(rank + 1, file - 1)->getOccupant() != nullptr && board->
                getSquareAt(rank + 1, file - 1)->getOccupant()->getColor() == this->getColor())) {
            moveableSpaces.push_back(board->getSquareAt(rank + 1, file - 1));
        }
    }
    // Rank + 1, File + 1
    if ((0 < rank + 1 && rank + 1 <= 8) && (0 < file + 1 && file + 1 <= 8)) {
        if (!(board->getSquareAt(rank + 1, file + 1)->getOccupant() != nullptr && board->
                getSquareAt(rank + 1, file + 1)->getOccupant()->getColor() == this->getColor())) {
            moveableSpaces.push_back(board->getSquareAt(rank + 1, file + 1));
        }
    }
    // Rank, File - 1
    if ((0 < rank && rank <= 8) && (0 < file - 1 && file - 1 <= 8)) {
        if (!(board->getSquareAt(rank, file - 1)->getOccupant() != nullptr && board->
                getSquareAt(rank, file - 1)->getOccupant()->getColor() == this->getColor())) {
            moveableSpaces.push_back(board->getSquareAt(rank, file - 1));
        }
    }
    // Rank, File + 1
    if ((0 < rank && rank <= 8) && (0 < file + 1 && file + 1 <= 8)) {
        if (!(board->getSquareAt(rank, file + 1)->getOccupant() != nullptr && board->
                getSquareAt(rank, file + 1)->getOccupant()->getColor() == this->getColor())) {
            moveableSpaces.push_back(board->getSquareAt(rank, file + 1));
        }
    }
    // Rank - 1, File
    if ((0 < rank - 1 && rank - 1 <= 8) && (0 < file && file <= 8)) {
        if (!(board->getSquareAt(rank - 1, file)->getOccupant() != nullptr && board->
                getSquareAt(rank - 1, file)->getOccupant()->getColor() == this->getColor())) {
            moveableSpaces.push_back(board->getSquareAt(rank - 1, file));
        }
    }
    // Rank - 1, File + 1
    if ((0 < rank - 1 && rank - 1 <= 8) && (0 < file + 1 && file + 1<= 8)) {
        if (!(board->getSquareAt(rank - 1, file + 1)->getOccupant() != nullptr && board->
                getSquareAt(rank - 1, file + 1)->getOccupant()->getColor() == this->getColor())) {
            moveableSpaces.push_back(board->getSquareAt(rank - 1, file + 1));
        }
    }
    // Rank - 1, File - 1
    if ((0 < rank - 1 && rank - 1 <= 8) && (0 < file - 1 && file - 1 <= 8)) {
        if (!(board->getSquareAt(rank - 1, file - 1)->getOccupant() != nullptr && board->
                getSquareAt(rank - 1, file - 1)->getOccupant()->getColor() == this->getColor())) {
            moveableSpaces.push_back(board->getSquareAt(rank - 1, file - 1));
        }
    }
    return moveableSpaces;
}
