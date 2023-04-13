#pragma once
#include"Piece.h"
#include"Sprite2D.h"
#include<set>
class GameBoard 
{

private:

	std::shared_ptr<Sprite2D>			m_frame;
	std::shared_ptr<Sprite2D>			m_background;
	std::vector<std::pair<int,int>>		m_click;
	std::set<std::pair<int, int>>		m_destroyList;
	int									m_moveSpeed;
	bool								m_isSwapping;
	bool								m_isRefilling;
	float								m_standbyTime;



public:
	std::shared_ptr<Sprite2D>								m_selected_piece;
	std::shared_ptr<Sprite2D>								m_selected_piece2;
	std::vector < std::vector<std::shared_ptr<Piece>>>		m_board;
	GameBoard();
	~GameBoard();
	void Init();

	bool							IsSwapping();
	bool							IsRefilling();

	bool							SameType(std::vector<std::pair<int,int>> pieceList);
	bool							HasAnAvailableMove(); //check if there are any available move
	std::vector<std::vector<int>>	GetAvailableMoveList();
	bool							HasAnMatch(); //Check if there are at least 3 pieces matching together
	bool							CanSwapTwoPiece(int lastRow, int lastCol, int curRow, int curCol);  //check if the swap is available by check the same neighbor pieces 

	void							SwapTwoPiece(int lastRow,int lastCol,int curRow,int curCol);  //Swap 2 piece
	void							SwapTwoSelectedPiece(int lastRow, int lastCol, int curRow, int curCol);  //Swap 2 piece
	void							ChangePositionOfTwoPiece(int lastRow, int lastCol, int curRow, int curCol,float deltaTime);

	void							SetDestroyList(std::set<std::pair<int, int>>list);
	std::set<std::pair<int, int>>	GetDestroyList();
	std::set<std::pair<int, int>>	GetPieceIndexMatchedList();
	std::set<std::pair<int, int>>	GetPieceIndexType(int type);

	std::vector<int>				GetPieceTypeMatchedList(std::set<std::pair<int, int>> pieceIndexMatchedList);

	void							DestroyPieces(std::set<std::pair<int, int>> pieceIndexMatchedList); //Destroy pieces that match together

	void							RefillGameBoard(); //Refill Gameboard after destroy but wrong position;
	void							RefillPositionGameBoard(float deltaTime); //Dropping the piece 
	void							Draw();
	//void Update(float deltaTime);
};