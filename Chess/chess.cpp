// blopez17@georgefox.edu
// Assignment 10
// 2019-04-29

#include "Game.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <vector>
#include "Square.h"
#include "Piece.h"
#include "Player.h"
#include "King.h"
using namespace std;

/**
 * This is the main method running the chess game
 */
int main(int, char*[]) {
    string AI;
    bool playWithAI = false;
//    cout << "Do You Want To Play With Al Gore? (Y/anything): ";
//    getline(cin, AI);
//    if (AI == "Y" || AI == "y") {
//        playWithAI = true;
//    }
    // Start the game
    Game::initialize();
    int moveFromRank;
    int moveFromFile;
    int moveToFile;
    int moveToRank;
    bool AIturn;
    bool gameOver = false;
    bool offerTie = false;
    bool inCheck = false;
    Player* player = Game::getCurrentPlayer();
    string movement;
    bool isValidMove;
    Board* board = Board::getInstance();
    // This will have two sections, one for normal movement, and another for special inputs
    while (!gameOver) {
        AIturn = false;
        isValidMove = true;
        if (inCheck) {
            cout << player->getName() << " is in Check, defend the King!" << endl;
        }
        // Get the move, or let the AI make a move
        if (playWithAI && player->getKing()->getColor() == "W") {
            cout << player->getName() << " enter your move: ";
            getline(cin, movement);
        }
        else if (playWithAI) {
            AIturn = true;
            isValidMove = true;
            // Isn't this funny? Al-Gor-Rythm?
            cout << " Al Gore Makes a Move! " << endl;
            Game::getAIMove();
            // Reset Movement
            movement = " ";
        }
        else {
            cout << player->getName() << " enter your move: ";
            getline(cin, movement);
        }
        // Normal movements
        // Check Input
        if (!AIturn) {
            if (movement.length() != 5 && movement.length() != 6) {
                isValidMove = false;
            }
            // Check to see if 3rd character is a space
            else if (movement.at(2) != ' ') {
                isValidMove = false;
            }
            // Check to see if the trailing input is a "="
            else if (movement.length() == 6 && movement.at(5) != '=') {
                isValidMove = false;
            }
        }
        // If the input is of the right size
        if (isValidMove && !AIturn) {
            // Get the values of the input, based on the ACCII values
            moveFromFile = (int)movement.at(0) - 96;
            moveFromRank = (int)movement.at(1) - 48;
            moveToFile = (int)movement.at(3) - 96;
            moveToRank = (int)movement.at(4) - 48;
            // Check if valid is within the accepted range
            if (1 > moveFromFile | moveFromFile > 8) {
                isValidMove = false;
            }
            else if (1 > moveFromRank | moveFromRank > 8) {
                isValidMove = false;
            }
            else if (1 > moveToFile | moveToFile > 8) {
                isValidMove = false;
            }
            else if (1 > moveToRank | moveToRank > 8) {
                isValidMove = false;
            }
            // Check to see if the requested piece is non-null
            else if (board->getSquareAt(moveFromRank, moveFromFile)->getOccupant() == NULL) {
                isValidMove = false;
            }
        }
        // Do Input
        if (isValidMove && !AIturn) {
            // Square that the piece will move to
            Square* movedToSquare = board->getSquareAt(moveToRank, moveToFile);
            // The moved piece
            Piece* movedPiece = board->getSquareAt(moveFromRank, moveFromFile)->getOccupant();
            if (movedPiece->getColor() != player->getKing()->getColor()) {
                isValidMove = false;
            }
            else {
                // Actually confirm and move the piece
                int checkCheck = movedPiece->moveTo(*movedToSquare, *player);
                // Player put opponent in check
                if (checkCheck == 1) {
                    inCheck = true;
                }
                else {
                    inCheck = false;
                }
                if (checkCheck == 2) {
                    cout << "\nYou put yourself in check!" << endl;
                    isValidMove = false;
                }
                else if (checkCheck == 3) {
                    isValidMove = false;
                }
            }
        }
        // Special movements
        if (movement == "0-0") {
            if (!board->canKingSideCastle(player)) {
                isValidMove = false;
            }
            else {
                isValidMove = true;
            }
        }
        else if (movement == "0-0-0") {
            if (!board->canQueenSideCastle(player)) {
                isValidMove = false;
            }
            else {
                isValidMove = true;
            }
        }
        //Lay Down the King
        int kingRank = player->getKing()->getLocation()->getRank();
        int kingFile = player->getKing()->getLocation()->getFile();
        if (kingRank == moveFromRank && kingRank == moveToRank) {
            if (kingFile == moveToFile && kingFile == moveFromFile) {
                gameOver = true;
                cout << "GIVE UP" << endl;
                // To avoid the end of game message
                isValidMove = true;
            }
        }
        //Offering a Draw
        // Accept or decline the draw
        if (offerTie) {
            if (movement.length() == 1 && movement.at(0) == '=') {
                gameOver = true;
            }
            else {
                offerTie = false;
            }
        }
        // Offer Draw
        if (movement.length() == 6 &&  movement.at(5) == '=') { // If move is valid
            isValidMove = true;
            offerTie = true;
        }
        //END OF GAME CHECKMATE
        if (movement.length() == 1 && movement.at(0) == '#') {
            if (inCheck) {
                cout << "CHECKMATE!" << endl;
                gameOver = true;
                isValidMove = true;
            }
        }
        //CHECK FOR CHECKMATE
        if (inCheck) {
            if (board->checkForCheckmate()) {
                gameOver = true;
                cout << "CHECKMATE!";
            }
        }
        //ROTATE PLAYER
        if (isValidMove && !gameOver) {
            player = Game::getNextPlayer();
            board->display();
        }
        else if (!isValidMove) {
            cout << "\n-------------INVALID MOVE-------------" << endl;
        }
    }
    board->display();
    cout << "Done, Thanks For Playing!" << endl;
    //Deconstruct the game
    delete Board::getInstance();
    return 0;
}
