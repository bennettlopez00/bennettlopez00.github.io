// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Queen.h"
#include "Game.h"
#include "Board.h"
#include <iostream>
#include <string>
#include "Square.h"
#include "Piece.h"
#include "Rook.h"
using namespace std;

Queen::Queen(string symbol, string color): Piece(symbol, color) {}

bool Queen::canMoveTo(Square* location) {
    bool canMove = false;
    vector<Square*> moveableSpaces = this->getMovableSpaces();
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

vector<Square*> Queen::getMovableSpaces() {
    // Gets both horizontal and vertical spaces
    vector<Square*> horizontal = this->getHorizontalSpaces();
    vector<Square*> vertical = this->getVerticalSpaces();
    // Combine the vertical and horizontal spaces
    for (auto piece : horizontal) {
        vertical.push_back(piece);
    }
    return vertical;
}
