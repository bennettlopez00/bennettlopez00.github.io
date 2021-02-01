// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Knight.h"
#include "Board.h"
#include "Square.h"
#include "Piece.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Knight::Knight(string symbol, string color): Piece(symbol, color) {}

bool Knight::canMoveTo(Square* location) {
    bool canMove = false;
    // Set of valid moves in the square
    vector<Square*> moveableSpaces;
    // All possible moves for the Knight
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

vector<Square*> Knight::getMovableSpaces() {
    // Set of valid moves in the square
    vector<Square*> moveableSpaces;
    // Rank and File of the current Knight Piece
    int file = this->getLocation()->getFile();
    int rank = this->getLocation()->getRank();
    Board* board = Board::getInstance();
    // All possible moves for the Knight
    // Rank + 1, File - 2
    if ((0 < rank + 1 && rank + 1 <= 8) && (0 < file - 2 && file - 2 <= 8)) {
        moveableSpaces.push_back(board->getSquareAt(rank + 1, file - 2));
    }
    // Rank + 1, File + 2
    if ((0 < rank + 1 && rank + 1 <= 8) && (0 < file + 2 && file + 2 <= 8)) {
        moveableSpaces.push_back(board->getSquareAt(rank + 1, file + 2));
    }
    // Rank - 1, File - 2
    if ((0 < rank - 1 && rank - 1 <= 8) && (0 < file - 2 && file - 2 <= 8)) {
        moveableSpaces.push_back(board->getSquareAt(rank - 1, file - 2));
    }
    // Rank - 1, File + 2
    if ((0 < rank - 1 && rank - 1 <= 8) && (0 < file + 2 && file + 2 <= 8)) {
        moveableSpaces.push_back(board->getSquareAt(rank - 1, file + 2));
    }
    // Rank + 2, File - 1
    if ((0 < rank + 2 && rank + 2 <= 8) && (0 < file - 1 && file - 1 <= 8)) {
        moveableSpaces.push_back(board->getSquareAt(rank + 2, file - 1));
    }
    // Rank + 2, File + 1
    if ((0 < rank + 2 && rank + 2 <= 8) && (0 < file + 1 && file + 1 <= 8)) {
        moveableSpaces.push_back(board->getSquareAt(rank + 2, file + 1));
    }
    // Rank - 2 , File + 1
    if ((0 < rank - 2 && rank - 2 <= 8) && (0 < file + 1 && file + 1 <= 8)) {
        moveableSpaces.push_back(board->getSquareAt(rank - 2, file + 1));
    }
    // Rank - 2, File - 1
    if ((0 < rank - 2 && rank - 2 <= 8) && (0 < file - 1 && file - 1 <= 8)) {
        moveableSpaces.push_back(board->getSquareAt(rank - 2, file - 1));
    }
    return moveableSpaces;
}
