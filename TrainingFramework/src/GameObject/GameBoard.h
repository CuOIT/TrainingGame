#pragma once
#include"Piece.h"
#include"Sprite2D.h"
#include<set>
class GameBoard : public Sprite2D
{

private:
	std::shared_ptr<Sprite2D>			m_frame;
	std::shared_ptr<Sprite2D>			m_background;
	std::vector<std::pair<int,int>>		m_click;
	int									m_moveSpeed;
	bool								m_isSwapping;
	bool								m_isRefilling;



public:
	float								m_standbyTime;
	std::shared_ptr<Sprite2D>			m_selected_piece;
	std::shared_ptr<Sprite2D>			m_selected_piece2;
	std::vector < std::vector<std::shared_ptr<Piece>>> m_board;
	GameBoard();
	~GameBoard();
	void Init();

	int GetMoveSpeedOfPieceDrop() {
		return m_moveSpeed;
	}
	bool IsSwapping() {
		return m_isSwapping;
	}
	bool IsRefilling() {
		return m_isRefilling;
	}
	bool HasAnAvailableMove(); //check if there are any available move
	std::set<std::pair<int, int>> GetMatchList();
	bool SameType(int lastRow, int lastCol, int curRow, int curCol);
	bool HasAnMatch(); //Check if there are at least 3 pieces matching together
	std::vector<std::vector<int>> GetAvailableMoveList();
	bool CanSwapTwoPiece(int lastRow, int lastCol, int curRow, int curCol);  //check if the swap is available by check the same neighbor pieces 
	void SwapTwoPiece(int lastRow,int lastCol,int curRow,int curCol);  //Swap 2 piece
	void ChangePositionOfTwoPiece(int lastRow, int lastCol, int curRow, int curCol,float deltaTime);
	void SwapTwoSelectedPiece(int lastRow, int lastCol, int curRow, int curCol);  //Swap 2 piece
	void DestroyPieces(std::set<std::pair<int, int>>); //Destroy pieces that match together
	void RefillGameBoard(); //Refill Gameboard after destroy but wrong position;
	void RefillPositionGameBoard(float deltaTime); //Dropping the piece 
	void Draw();
	//void Update(float deltaTime);
};