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
	};
public:

	GameField() {};
	~GameField();
	GameField(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy);
	void Init(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy);

	void HandleClick(float x, float y);

	void								Calculate(std::vector<int> pieceList,bool isPlayer);
	void								SetPhase(Phase phase);
	Phase								getPhase();
	void								BotMove();

	void Update(float deltaTime);
	void Draw();
	std::shared_ptr<GameBoard>			m_gameBoard;
private:
	bool								m_currentTurn;
	Phase								m_phase;
	float								m_standbyTime;
	std::vector<std::pair<int, int>>	m_click;
	std::shared_ptr<Player>				m_player;
	std::shared_ptr<StatusBar>			m_PStatusBar;
	std::shared_ptr<StatusBar>			m_EStatusBar;
	std::shared_ptr<Entity>				m_enemy;
	std::queue<bool>					m_turn;

};