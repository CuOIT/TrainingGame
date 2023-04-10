#pragma once
#include"Entity.h"
#include"Player.h"
#include"GameBoard.h"
#include"StatusBar.h"
#include<queue>
class GameField {
	enum class Phase {
		BEGIN_PHASE,
		BASE_PHASE,
		SWAP_PHASE,
		DESTROY_PHASE,
		REFILL_PHASE,
		END_PHASE
	};
public:

	GameField() {};
	~GameField();
	GameField(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy);
	void Init(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy);

	void HandleClick(float x, float y);
	void Update(float deltaTime);

	void								Calculate(std::vector<int> pieceList,bool isPlayer);
	void								SetPhase(Phase phase);
	Phase								getPhase();
	void								BotMove();
	void Draw();
	
private:
	bool								m_currentTurn;
	std::shared_ptr<Sprite2D>			m_turnPoint;
	Phase								m_phase;
	float								m_standbyTime;
	std::vector<std::pair<int, int>>	m_click;
	std::vector<int>				m_pieceList;
	std::shared_ptr<Player>				m_player;
	std::shared_ptr<StatusBar>			m_PStatusBar;
	std::shared_ptr<StatusBar>			m_EStatusBar;
	std::shared_ptr<Entity>				m_enemy;
	std::shared_ptr<GameBoard>			m_gameBoard;
	std::queue<bool>					m_turn;

};