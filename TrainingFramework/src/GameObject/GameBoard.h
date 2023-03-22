#pragma once
#include"Piece.h"
class GameBoard 
{
private:
	std::vector < std::vector<Piece>> m_gameBoard;
public:
	GameBoard();
	~GameBoard();
	void generateGameBoard(); //generate a new game board 
	bool hasAnAvailableMove(); //check if there are any available move
	bool hasAnMatch(); //Check if there are at least 3 pieces matching together
	bool canSwapTwoPiece();  //check if the swap is available by check the same neighbor pieces 
	void swapTwoPiece();  //Swap 2 piece
	void destroyPieces(std::vector<std::vector<int>>); //Destroy pieces that match together
	void refillGameBoard(); //Refill Gameboard after destroy;
};