#pragma once
#include"Piece.h"
#include"Sprite2D.h"
#include<set>
class GameBoard : public Sprite2D
{
	enum class Phase {
		BASE_PHASE,
		SWAP_PHASE,
		DESTROY_PHASE,
		REFILL_PHASE, 
	};
private:
	std::shared_ptr<Sprite2D>			m_frame;
	std::vector<std::pair<int,int>>		m_click;
	std::shared_ptr<Sprite2D>			m_selected_piece;
	Phase								m_phase;
	int									m_standbyTime;


public:
	std::vector < std::vector<std::shared_ptr<Piece>>> m_board;
	GameBoard();
	~GameBoard();
	void Init();
	void SetPhase(Phase phase) {
		m_phase = phase;
	}
	Phase getPhase() {
		return m_phase;
	}
	void GenerateGameBoard(); //generate a new game board 
	bool HasAnAvailableMove(); //check if there are any available move
	std::set<std::pair<int,int>> GetMatchList();
	bool HasAnMatch(); //Check if there are at least 3 pieces matching together
	void HandleClick(float _x,float _y);
	bool CanSwapTwoPiece(int lastRow, int lastCol, int curRow, int curCol);  //check if the swap is available by check the same neighbor pieces 
	void SwapTwoPiece(int lastRow,int lastCol,int curRow,int curCol);  //Swap 2 piece
	void SwapTwoSelectedPiece(int lastRow, int lastCol, int curRow, int curCol);  //Swap 2 piece
	void DestroyPieces(std::set<std::pair<int, int>>); //Destroy pieces that match together
	void RefillGameBoard(); //Refill Gameboard after destroy;
	void Draw();
	void Update(float deltaTime);
};