// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Rook.h"
#include "Piece.h"
#include "Board.h"
#include "Square.h"
#include <string>
#include <iostream>
#include <vector>

Rook::Rook(string symbol, string color): Piece(symbol, color) {}

bool Rook::canMoveTo(Square* location) {
    bool canMove = false;
    vector<Square*> moveableSpaces = this->getMovableSpaces();
    // Testing to see if the requested move is an available move
    for(int i = 0; i < moveableSpaces.size(); i++) {
        if (moveableSpaces[i] == location) {
            canMove = true;
        }
    }
    // Confirm that the end piece isn't a similar color piece
    if (location->getOccupant() != nullptr && location->getOccupant()->getColor()
            == this->getColor()) {
        canMove = false;
    }
    return canMove;
}

vector<Square*> Rook::getMovableSpaces() {
    return this->getVerticalSpaces();
}
