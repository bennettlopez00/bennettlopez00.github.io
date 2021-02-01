// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Pawn.h"
#include <string>
#include <iostream>
#include "Square.h"
#include "Board.h"
#include "Piece.h"
#include <vector>
#include "Queen.h"
using namespace std;

Pawn::Pawn(string symbol, string color): Piece(symbol, color) {_delegate = false;}

bool Pawn::canMoveTo(Square* movedToSquare) {
    bool canMove = false;
    // Set of valid moves in the square
    vector<Square*> moveableSpaces;
    /**
     * There needs to be a difference between a black and white pawn, due to the fact that
     * the movements for pawn are asymmetric, and require different square difference due to
     * the side of the board they are on.
     *
     * This delegate determines if the piece has reached the end of the board. If it has, the
     * canMoveTo changes the piece to have the skin of a queen and the movements of one as
     * well
     */
    if (!_delegate) {
        // Get All The Movable Spaces
        moveableSpaces = this->getMovableSpaces();
        // Testing to see if the requested move is an available move
        for(int i = 0; i < moveableSpaces.size(); i++) {
            if (moveableSpaces[i] == movedToSquare) {
                // Cannot move onto a square with a piece of the same color, this applies for all
                // Movements and attacks made by the Pawn
                if (movedToSquare->getOccupant() != nullptr && this->getColor() ==
                        movedToSquare->getOccupant()->getColor()) {
                    canMove = false;
                }
                else {
                    canMove = true;
                }
            }
        }
    }
    // This is a copy of the Queen CanMoveTo. This is because calling a method from the
    // Queen class would require an instance of a Queen, and not an instance of a pawn, which
    // is what this seciton is trying to move
    else {
    vector<Square*> moveableSpaces = this->getHorizontalSpaces();
    // Testing to see if the requested move is an available move
    for(int i = 0; i < moveableSpaces.size(); i++) {
        if (moveableSpaces[i] == movedToSquare) {
            canMove = true;
        }
    }
    vector<Square*> HorizontalSpaces= this->getVerticalSpaces();
    // Testing to see if the requested move is an available move
    for(int i = 0; i < HorizontalSpaces.size(); i++) {
        if (HorizontalSpaces[i] == movedToSquare) {
            canMove = true;
        }
    }
    // Confirm that the end piece isn't a similar color piece
    if (movedToSquare->getOccupant() != nullptr && movedToSquare->getOccupant()->getColor()
            == this->getColor()) {
        canMove = false;
    }
    }
    // This changes the skin of the pawn to mask as a queen. Rank 1 and 8 because the pawns can't
    // Move backwards, so the only possible reason for a pawn to be at either end, it if it's an
    // opponent
    if (canMove == true && (movedToSquare->getRank() == 8 || movedToSquare->getRank() == 1)) {
        _delegate = true;
        string setSymbol;
        if (this->getColor() == "W") {
            setSymbol = "♕";
        }
        else {
            setSymbol = "♛";
        }
    }
    // Check to see if moving on a piece
    return canMove;
}

vector<Square*> Pawn::getMovableSpaces() {
    /**
     * ** NOTE **
     * This gets the possible movements for the Pawn. This repeats some of the logic in pawn
     * canMoveTo, but instead of returning a boolean, it returns a list of the possible squares.
     * This could have been combined into one method, but that would require repeated logic
     * of determining if a move was in the possible moves, so to make the code more readable, and
     * to avoid scattered repeated logic, the methods are divided up.
     */
    // Set of valid moves in the square
    vector<Square*> moveableSpaces;
    // Rank and File of the current Knight Piece
    int file = this->getLocation()->getFile();
    int rank = this->getLocation()->getRank();
    Board* board = Board::getInstance();
    if (this->getColor() == "W") {
        // Rank + 1, File - 1 [ ATTACK ] // Plus the attack condition
        if ((0 < rank + 1 && rank + 1 <= 8) && (0 < file - 1 && file - 1 <= 8)) {
            // Since pawns have an attack only movement, here is checked for a piece
            if (board->getSquareAt(rank + 1, file - 1)->getOccupant() != nullptr && board->
                    getSquareAt(rank + 1, file - 1)->getOccupant()->getColor() == "B") {
                moveableSpaces.push_back(board->getSquareAt(rank + 1, file - 1));
            }
        }
        // Rank + 1, File + 1 [ ATTACK ] // Plus the attack condition
        if ((0 < rank + 1 && rank + 1 <= 8) && (0 < file + 1 && file + 1 <= 8)) {
            if (board->getSquareAt(rank + 1, file + 1)->getOccupant() != nullptr && board->
                    getSquareAt(rank + 1, file + 1)->getOccupant()->getColor() == "B") {
                moveableSpaces.push_back(board->getSquareAt(rank + 1, file + 1));
            }
        }
        // Rank + 1, File
        if ((0 < rank + 1 && rank + 1 <= 8)) {
            if (!board->getSquareAt(rank + 1, file)->isOccupied()) {
                moveableSpaces.push_back(board->getSquareAt(rank + 1, file));
            }
        }
        // Rank + 2, File [ Conditional Move ] // Plus the moved Condition
        if ((0 < rank + 2 && rank + 2 <= 8) && !this->hasMoved()) {
            if (!board->getSquareAt(rank + 1, file)->isOccupied() && !board->getSquareAt
                    (rank + 2, file)->isOccupied()) {
                moveableSpaces.push_back(board->getSquareAt(rank + 2, file));
            }
        }
    }
    // If the piece is black
    else {
        // Since pawns have an attack only movement, here is checked for a piece
        // Rank - 1, File - 1 [ ATTACK ] // Plus the attack condition
        if ((0 < rank - 1 && rank - 1 <= 8) && (0 < file - 1 && file - 1 <= 8)) {
            if (board->getSquareAt(rank - 1, file - 1)->getOccupant() != nullptr && board->
                    getSquareAt(rank - 1, file - 1)->getOccupant()->getColor() == "W") {
                moveableSpaces.push_back(board->getSquareAt(rank - 1, file - 1));
            }
        }
        // Rank - 1, File + 1 [ ATTACK ] // Plus the attack condition
        if ((0 < rank - 1 && rank - 1 <= 8) && (0 < file + 1 && file + 1 <= 8)) {
            if (board->getSquareAt(rank - 1, file + 1)->getOccupant() != nullptr && board->
                    getSquareAt(rank - 1, file + 1)->getOccupant()->getColor() == "W") {
                moveableSpaces.push_back(board->getSquareAt(rank - 1, file + 1));
            }
        }
        // Rank - 1, File
        if ((0 < rank - 1 && rank - 1 <= 8)) {
            if (!board->getSquareAt(rank - 1, file)->isOccupied()) {
                moveableSpaces.push_back(board->getSquareAt(rank - 1, file));
            }
        }
        // Rank - 2, File [ Conditional Move ] // Plus the moved Condition
        if ((0 < rank - 2 && rank - 2 <= 8) && !this->hasMoved()) {
            if (!board->getSquareAt(rank - 1, file)->isOccupied() && !board->getSquareAt
                    (rank - 2, file)->isOccupied()) {
                moveableSpaces.push_back(board->getSquareAt(rank - 2, file));
            }
        }
    }
    return moveableSpaces;
}
