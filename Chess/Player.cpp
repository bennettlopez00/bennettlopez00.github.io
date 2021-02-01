// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "King.h"
#include "Piece.h"
#include "Player.h"
#include "Game.h"
#include <string>
#include <set>
#include <vector>
using namespace std;

Player::Player(string name, King* king, set<Piece*>* pieces): _pieces(pieces) {
    _name = name;
    _king = king;
}

string Player::getName() {
    return _name;
}

King* Player::getKing() {
    return _king;
}

set<Piece*>* Player::getPieces() {
    return _pieces;
}

void Player::losePiece(Piece* piece) {
    _pieces->erase(piece);
}

void Player::capture(Piece* piece) {
    // Capture pieces actively adds the piece to the player collection of pieces, as well as
    // removes it from the opponents list of pieces
    Player* opponent = Game::getOpponentOf(this);
    opponent->losePiece(piece);
    _capturedPieces.push_back(piece);
}
