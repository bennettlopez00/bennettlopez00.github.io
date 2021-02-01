// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Square.h"
#include "Piece.h"
class Piece;

Square::Square(int rank, int file) {
    _rank = rank;
    _file = file;
    _occupant = nullptr;
}

int Square::getRank() {
    return _rank;
}

int Square::getFile() {
    return _file;
}

bool Square::isOccupied() {
    bool isOccupied = true;
    if (_occupant == NULL) {
        isOccupied = false;
    }
    return isOccupied;
}

Piece* Square::getOccupant() {
    return _occupant;
}

void Square::setOccupant(Piece* occupant) {
    _occupant = occupant;
    occupant->setLocation(this);
}

void Square::setOccupantNull() {
    _occupant = nullptr;
}

ostream& operator<< (ostream& output, const Square& square) {
    output << "Rank: " << square._rank << " File: " << square._file << " Occupant: ";
    if (square._occupant == NULL) {
        cout << "NULL";
    }
    else {
        cout << *square._occupant;
    }
    return output;
}
