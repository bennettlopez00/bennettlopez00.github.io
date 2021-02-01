// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Board.h"
#include "Square.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"
#include "Piece.h"
#include "Game.h"
#include "Player.h"
#include <string>
#include <ostream>
#include <string>
#include <cstdlib>
#include <set>
#include <vector>
using namespace std;

// These are the constants for displaying the board
const string BOARDSEPARATOR = "  +----+----+----+----+----+----+----+----+";
const string HORIZONTALSEPARATOR = "     a    b    c    d    e    f    g    h    ";
// This allocates the instance of the board to nothing, and once initialized, it cannot again
Board* Board::_instance = 0;

Board::Board() {
    // The dynamic memory allocation is released in the destructor
    for (int rowNum = DIMENSION; rowNum > 0; --rowNum) {
        for (int columnNum = 1; columnNum <= DIMENSION; ++columnNum) {
            Square* addedSquare = new Square(rowNum, columnNum);
            _squares.push_back(addedSquare);
        }
    }
    // Add Queen
    Piece* queenWhite = new Queen("♕", "W");
    placePiece(queenWhite, 1, 4);

    Piece* queenBalck = new Queen("♛", "B");
    placePiece(queenBalck, 8, 4);

    // Add Knight
    Piece* knightWhiteOne = new Knight("♘", "W");
    placePiece(knightWhiteOne, 1, 2);

    Piece* knightWhiteTwo = new Knight("♘", "W");
    placePiece(knightWhiteTwo, 1, 7);

    Piece* knightBlackOne = new Knight("♞", "B");
    placePiece(knightBlackOne, 8, 2);

    Piece* knightBlackTwo = new Knight("♞", "B");
    placePiece(knightBlackTwo, 8, 7);

    // Add Bishop
    Piece* bishopWhiteOne = new Bishop("♗", "W");
    placePiece(bishopWhiteOne, 1, 3);

    Piece* bishopWhiteTwo = new Bishop("♗", "W");
    placePiece(bishopWhiteTwo, 1, 6);

    Piece* bishopBlackOne = new Bishop("♝", "B");
    placePiece(bishopBlackOne, 8, 3);

    Piece* bishopBlackTwo = new Bishop("♝", "B");
    placePiece(bishopBlackTwo, 8, 6);

    // Add Pawn
    for (int row = 1; row <= 8; ++row) {
        Piece* pawnBlack = new Pawn("♟", "B");
        placePiece(pawnBlack, 7, row);
    }

    for (int row = 1; row <= 8; ++row) {
        Piece* pawnBlack = new Pawn("♙", "W");
        placePiece(pawnBlack, 2, row);
    }

    // Add King
    Piece* whiteKing = new King("♔", "W");
    placePiece(whiteKing, 1, 5);

    Piece* balckKing = new King("♚", "B");
    placePiece(balckKing, 8, 5);

    // Add Rook
    Piece* balckRookOne = new Rook("♜", "B");
    placePiece(balckRookOne, 8, 1);

    Piece* blackRookTwo = new Rook("♜", "B");
    placePiece(blackRookTwo, 8, 8);

    Piece* whiteRookOne = new Rook("♖", "W");
    placePiece(whiteRookOne, 1, 1);

    Piece* whiteRookTwo = new Rook("♖", "W");
    placePiece(whiteRookTwo, 1, 8);
    // This block takes all the pieces added, and adds them to a list based on the color, and
    // a total list, used to delete all the pieces after the game exits.
    for (int rowNum = DIMENSION; rowNum > 0; --rowNum) {
        for (int columnNum = 1; columnNum <= DIMENSION; ++columnNum) {
             if (getSquareAt(rowNum, columnNum)->getOccupant() != nullptr)  {
                 // Set Black Pieces, White Pieces and Total Pieces
                 if (getSquareAt(rowNum, columnNum)->getOccupant()->getColor() == "W") {
                     _boardWhitePieces.insert(getSquareAt(rowNum, columnNum)->getOccupant());
                 }
                 else {
                     _boardBlackPieces.insert(getSquareAt(rowNum, columnNum)->getOccupant());
                 }
                 // Add the piece regardless of color
                 _totalPieces.insert(getSquareAt(rowNum, columnNum)->getOccupant());
             }
        }
     }
}

Board::~Board() {
    // Removes all the Squares from memory
    for (int columnNum = 1; columnNum <= DIMENSION; ++columnNum) {
        for (int rowNum = 1; rowNum <= DIMENSION; ++rowNum) {
            delete this->getSquareAt(columnNum, rowNum);
        }
    }
    // Removes all the Pieces from memory
    for (auto piece : _totalPieces) {
        delete piece;
    }
}

Board* Board::getInstance() {
    // This singleton pattern only allows for one instance of the board
    if (_instance == 0) {
        _instance = new Board();
    }
    return _instance;
}

Square* Board::getSquareAt(int rank, int file) {
    /**
     * The board is populated by squares in a vector, going by rank, from left to right. Because
     * of this ordering, finding the index of the square in the vector can simply be the total
     * number of squares that came before it. The equation is DIMENSION * Rank + File. This will
     * give the index of a given square, with a constant complexity.
     *
     * The Rank -1 is to account for the current rank, and the outside -1 is because the vertex is
     * zero based
     */
    // To change to descending format
    rank = abs(rank - 8) + 1;
    int index = (DIMENSION * (rank -1) - 1) + file;
    Square* returnSquare = _squares.at(index);
    return returnSquare;
}

void Board::display() {
    cout << "\n" << HORIZONTALSEPARATOR << "\n";
    cout << BOARDSEPARATOR << "\n";
    // Goes though each position on the board (Total of 64 calls)
    int downcounter = DIMENSION;
    for (int columnNum = DIMENSION; columnNum > 0; --columnNum) {
        cout << downcounter << " ";
        for (int rowNum = 1; rowNum <= DIMENSION; ++rowNum) {
            Piece* piece = getInstance()->getSquareAt(columnNum, rowNum)->getOccupant();
            // Display nothing if Null
            if (piece != nullptr) {
                cout << "| " << *(piece) <<  "  ";
            }
            else {
                cout << "|    ";
            }
        }
        cout << "| " << downcounter <<"\n";
        cout << BOARDSEPARATOR << "\n";
        downcounter -= 1;
    }
    cout << HORIZONTALSEPARATOR << "\n\n";
}

void Board::placePiece(Piece* addedPiece, int rank, int column) {
    Square* squareWQ = this->getSquareAt(rank, column);
    squareWQ->setOccupant(addedPiece);
}

int Board::checkForCheck(Player* player, Piece* removedPiece) {
    /**
     * The player is correspondent to the king of the player, so after a player makes a move, if
     * They put their own king in check, they re-do the move, but if the put the opponent in check
     * Then the check message is given. The return is an int, 0: No kings are in check, 1: Your own
     * king is in check, 2: Your opponents king is in check. Note that it doesn't matter if both kings
     * are in check, the player cannot actively put their king in check.
     */
    int returnInt = 0;
    Player* opponent = Game::getOpponentOf(player);
    Square* playerKingLocation = player->getKing()->getLocation();
    Square* opponentKingLocation = opponent->getKing()->getLocation();
    // Check all player pieces on opponent king
    for (auto piece : *player->getPieces()) {
         if (piece->canMoveTo(opponentKingLocation)){
             returnInt = 1;
         }
    }
    // Check all opponent pieces on player king
    // This overrides the previous check check due to order of operations, so it doesn't matter
    // if the player puts the opposing King in check if he puts his own king in check in the
    // Same move
    for (auto piece : *opponent->getPieces()) {
        if (piece != removedPiece) {
            // This is because the piece is given to the captured player if
            // The move does not put the plyer's own king in check
            if (piece->canMoveTo(playerKingLocation)){
                 returnInt = 2;
             }
        }
    }
    return returnInt;
}

bool Board::canKingSideCastle(Player* player) {
    // There are three pieces to castling (1) that the two right positions next to the king need to
    // Be vacant, (2) the king and bishop need to have not moved, (3) The king cannot move though
    // check, meaning that the king can't castle if any of the moved positions create check.
    Board* board = Board::getInstance();
    bool canCastle = true;
    King* king = player->getKing();
    Piece* castledPiece;

    if (king->getColor() == "W") {
        // If either piece has moved
        if (king->hasMoved() || (board->getSquareAt(1, 1) == nullptr && board->getSquareAt(1, 8)->getOccupant()->hasMoved())) {
            canCastle = false;
        }
        // If the two adjacent spaces are empty
        else if (board->getSquareAt(1, 6)->isOccupied() || board->getSquareAt(1, 7)->isOccupied()) {
            canCastle = false;
        }
        // If the King can move to the two locations w/o falling into check
        else if (!king->testForCheck(getSquareAt(1, 6)) || !king->testForCheck(getSquareAt(1, 7))) {
            canCastle = false;
        }
        // If all the conditions are met, move to castle
        else {
            board->getSquareAt(1, 7)->setOccupant(king);
            board->getSquareAt(1, 5)->setOccupantNull();
            castledPiece =  board->getSquareAt(1, 8)->getOccupant();
            board->getSquareAt(1, 6)->setOccupant(castledPiece);
            board->getSquareAt(1, 8)->setOccupantNull();
        }
    }
    else {
        // If either piece has moved
        if (king->hasMoved() || (board->getSquareAt(1, 1) == nullptr && board->getSquareAt(8, 8)->getOccupant()->hasMoved())) {
            canCastle = false;
        }
        // If the two adjacent spaces are empty
        else if (board->getSquareAt(8, 6)->isOccupied() || board->getSquareAt(8, 7)->isOccupied()) {
            canCastle = false;
        }
        // If the King can move to the two locations w/o falling into check
        else if (!king->testForCheck(getSquareAt(8, 6)) || !king->testForCheck(getSquareAt(8, 7))) {
            canCastle = false;
        }
        // If all the conditions are met, move to castle
        else {
            board->getSquareAt(8, 7)->setOccupant(king);
            board->getSquareAt(8, 5)->setOccupantNull();
            castledPiece =  board->getSquareAt(8, 8)->getOccupant();
            board->getSquareAt(8, 6)->setOccupant(castledPiece);
            board->getSquareAt(8, 8)->setOccupantNull();
        }
    }
    return canCastle;
}

bool Board::canQueenSideCastle(Player* player) {
    // There are three pieces to castling (1) that the three left positions next to the king need to
    // Be vacant, (2) the king and bishop need to have not moved, (3) The king cannot move though
    // check, meaning that the king can't castle if any of the moved positions create check.
    Board* board = Board::getInstance();
    bool canCastle = true;
    King* king = player->getKing();
    Piece* castledPiece;

    if (king->getColor() == "W") {
        // If either piece has moved
        if (king->hasMoved() || (board->getSquareAt(1, 1) == nullptr && board->getSquareAt(1, 1)->getOccupant()->hasMoved())) {
            canCastle = false;
        }
        // If the three adjacent spaces are empty
        else if (board->getSquareAt(1, 2)->isOccupied() || board->getSquareAt(1, 3)->isOccupied() || board->getSquareAt(1, 4)->isOccupied()) {
            canCastle = false;
        }
        // If the King can move to the three locations w/o falling into check
        else if (!king->testForCheck(getSquareAt(1, 2)) || !king->testForCheck(getSquareAt(1, 3)) || !king->testForCheck(getSquareAt(1, 4))) {
            canCastle = false;
        }
        // If all the conditions are met, move to castle
        else {
            board->getSquareAt(1, 3)->setOccupant(king);
            board->getSquareAt(1, 5)->setOccupantNull();
            castledPiece =  board->getSquareAt(1, 1)->getOccupant();
            board->getSquareAt(1, 4)->setOccupant(castledPiece);
            board->getSquareAt(1, 1)->setOccupantNull();
        }
    }
    else {
        // If either piece has moved
        if (king->hasMoved() || (board->getSquareAt(1, 1) == nullptr && board->getSquareAt(8, 1)->getOccupant()->hasMoved())) {
            canCastle = false;
        }
        // If the three adjacent spaces are empty
        else if (board->getSquareAt(8, 2)->isOccupied() || board->getSquareAt(8, 3)->isOccupied() || board->getSquareAt(8, 4)->isOccupied()) {
            canCastle = false;
        }
        // If the King can move to the three locations w/o falling into check
        else if (!king->testForCheck(getSquareAt(8, 2)) || !king->testForCheck(getSquareAt(8, 3)) || !king->testForCheck(getSquareAt(8, 4))) {
            canCastle = false;
        }
        // If all the conditions are met, move to castle
        else {
            board->getSquareAt(8, 3)->setOccupant(king);
            board->getSquareAt(8, 5)->setOccupantNull();
            castledPiece =  board->getSquareAt(8, 1)->getOccupant();
            board->getSquareAt(8, 4)->setOccupant(castledPiece);
            board->getSquareAt(8, 1)->setOccupantNull();
        }
    }
    return canCastle;
}

bool Board::checkForCheckmate() {
    /**
     * There are three ways to stop a check, (1) Move the king out of check, (2) Take the
     * attacking piece, (3) Put a piece in the path of the attacking piece. If any of these
     * moves can be done, without creating another check, then it isn't checkmate.
     */
    bool isCheckmate = true;
    // Possible movement stated above
    vector<Square*> possibleMoves;
    Player* player = Game::getCurrentPlayer();
    Player* opponent = Game::getOpponentOf(player);
    King* opponentKing = opponent->getKing();
    Piece* attackingPiece;
    // The possible moves the king can make.
    possibleMoves = opponentKing->getMovableSpaces();
    // Get all the king's possible moves, to see if the King can move out of check
    for (auto kingMove: possibleMoves) {
        // testForCheck moves the pieces to the predicted positions to see if it creates another
        // Form of check with the movement.
        if (opponentKing->testForCheck(kingMove)) {
            isCheckmate = false;
        }
    }
    // Remove the kings moves from the possible moves to block the offending piece
    possibleMoves.empty();
    // Get the offending Piece
    for (auto piece : *player->getPieces()) {
         if (piece->canMoveTo(opponentKing->getLocation())){
             attackingPiece = piece;
         }
    }
    // Get piece path
    // If the piece can't slide, then the only option is to take the piece
    if (typeid(attackingPiece) == typeid(King) || typeid(attackingPiece) == typeid(Knight)
            || typeid(attackingPiece) == typeid(Pawn)) {
        possibleMoves.push_back(attackingPiece->getLocation());
    }
    // If a piece can move between the offending piece and the king
    else {
        vector<Square*> possibleMoves = getAttackingPath(attackingPiece);
    }
    // Test to see if the opponent can move any of their pieces onto the attacking piece, or
    // The path of the attacking piece without creating check
    for (auto piece : *opponent->getPieces()) {
        for (auto space : possibleMoves) {
            if (typeid(attackingPiece) != typeid(King) && piece->canMoveTo(space)) {
                if (piece->testForCheck(space)) {
                    isCheckmate = false;
                }
            }
        }
    }
    return isCheckmate;
}

set<Piece*>* Board::getWhitePieces() {
    return &_boardWhitePieces;
}

set<Piece*>* Board::getBlackPieces() {
    return &_boardBlackPieces;
}

/**
 * This gets the attacking path of the piece, if the piece can move horizontally or vertically.
 * This code repeats some of the logic placed in Piece's getHorizontal and getDiagonal, except
 * That this method filters though the movable spaces, and determines the path, and not just
 * Every possible movement.
 */
vector<Square*> Board::getAttackingPath(Piece* attackingPiece) {
    /**
     * A couple of thing as assumed to be confirmed before calling this method. Firstly that the
     * the player is in check, so some piece can attack the King, secondly that the attacking
     * Piece is one that moves vertically and horizontally.
     */
    Board* board = Board::getInstance();
    // The player is the person with the king in check, which would be the opponent of the current
    // player
    Player* player = Game::getOpponentOf(Game::getCurrentPlayer());
    King* king = player->getKing();
    // The possible movable spaces
    vector<Square*> moveableSpaces;
    // The rank and file of the checked king
    int rank = king->getLocation()->getRank();
    int file = king->getLocation()->getFile() + 1;
    // This marker is triggered if the attacking piece is found, which skips over losts of the
    // Code found below
    bool isDone = false;

    // Get Left Horizontal
    while ((0 < file && file <= 8) && !isDone) {
        moveableSpaces.push_back(board->getSquareAt(rank, file));
        // Done if the piece is along this axis
        if (board->getSquareAt(rank, file) != nullptr && board->getSquareAt(rank, file)->
                getOccupant() == attackingPiece) {
            isDone = true;
        }
        file = file + 1;
    }
    if (!isDone) {
        moveableSpaces.clear();
    }
    // Reset File
    file = king->getLocation()->getFile() - 1;
    // Get Right Horizontal
    while ((0 < file && file <= 8) && !isDone) {
        moveableSpaces.push_back(board->getSquareAt(rank, file));
        if (board->getSquareAt(rank, file) != nullptr && board->getSquareAt(rank, file)->
                getOccupant() == attackingPiece) {
            isDone = true;
        }
        file = file - 1;
    }
    if (!isDone) {
        moveableSpaces.clear();
    }
    // Reset Rank and File
    file = king->getLocation()->getFile();
    rank = king->getLocation()->getRank() + 1;
    // Get Up Vertical
    while ((0 < rank && rank <= 8) && !isDone) {
        moveableSpaces.push_back(board->getSquareAt(rank, file));
        if (board->getSquareAt(rank, file) != nullptr && board->getSquareAt(rank, file)->
                getOccupant() == attackingPiece) {
            isDone = true;
        }
        rank = rank + 1;
    }
    if (!isDone) {
        moveableSpaces.clear();
    }
    // Reset Rank
    rank = king->getLocation()->getRank() - 1;
    // Get down Vertical
    while ((0 < rank && rank <= 8) && !isDone) {
        moveableSpaces.push_back(board->getSquareAt(rank, file));
        if (board->getSquareAt(rank, file) != nullptr && board->getSquareAt(rank, file)->
                getOccupant() == attackingPiece) {
            isDone = true;
        }
        rank = rank - 1;
    }
    if (!isDone) {
        moveableSpaces.clear();
    }
    // Moving on to the horizontal spaces
    rank = king->getLocation()->getRank() + 1;
    file = king->getLocation()->getFile() - 1;
    // 0 < Rank < 8, 0 < File < 8
    // Down Left
    while ((0 < rank && rank <= 8) && (0 < file && file <= 8) && !isDone) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            if (board->getSquareAt(rank, file) != nullptr && board->getSquareAt(rank, file)->
                    getOccupant() == attackingPiece) {
                isDone = true;
            }
            rank = rank + 1;
            file = file - 1;
    }
    if (!isDone) {
        moveableSpaces.clear();
    }
    rank = king->getLocation()->getRank() - 1;
    file = king->getLocation()->getFile() + 1;
    // 0 < Rank < 8, 0 < File < 8
    // Down Right
    while ((0 < rank && rank <= 8) && (0 < file && file <= 8) && !isDone) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            if (board->getSquareAt(rank, file) != nullptr && board->getSquareAt(rank, file)->
                    getOccupant() == attackingPiece) {
                isDone = true;
            }
            rank = rank - 1;
            file = file + 1;
    }
    if (!isDone) {
        moveableSpaces.clear();
    }
    // Reset Rank and File to next square
    rank = king->getLocation()->getRank() - 1;
    file = king->getLocation()->getFile() - 1;
    // 0 < Rank < 8, 0 < File < 8
    // Up Left
    while ((0 < rank && rank <= 8) && (0 < file && file <= 8) && !isDone) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            if (board->getSquareAt(rank, file) != nullptr && board->getSquareAt(rank,file)->
                    getOccupant() == attackingPiece) {
                isDone = true;
            }
            rank = rank - 1;
            file = file - 1;
    }
    if (!isDone) {
        moveableSpaces.clear();
    }
    rank = king->getLocation()->getRank() + 1;
    file = king->getLocation()->getFile() + 1;
    while ((0 < rank && rank <= 8) && (0 < file && file <= 8) && !isDone) {
            moveableSpaces.push_back(board->getSquareAt(rank, file));
            if (board->getSquareAt(rank, file) != nullptr && board->getSquareAt(rank, file)->
                    getOccupant() == attackingPiece) {
                isDone = true;
            }
            rank = rank + 1;
            file = file + 1;
    }
    if (!isDone) {
        moveableSpaces.clear();
    }
    return moveableSpaces;
}

