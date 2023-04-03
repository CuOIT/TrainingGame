#pragma once
#include"Entity.h"
#include"Player.h"
#include"GameBoard.h"
#include<queue>
class GameField {
	enum class Phase {
		BASE_PHASE,
		SWAP_PHASE,
		DESTROY_PHASE,
		REFILL_PHASE,
	};
public:

	GameField();
	~GameField();
	GameField(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy);
	void Init(std::shared_ptr<Player> player, std::shared_ptr<Entity> enermy);
	void HandleClick(float x, float y);
	void Update(float deltaTime);

	void Calculate();
	void Draw();;

	void SetPhase(Phase phase);
	Phase getPhase();
private:
	bool								m_currentTurn;
	Phase								m_phase;
	float								m_standbyTime;
	std::vector<std::pair<int, int>>	m_click;
	std::shared_ptr<Player>				m_player;
	std::shared_ptr<Entity>				m_enermy;
	std::shared_ptr<GameBoard>			m_gameBoard;
	std::queue<bool>					m_turn;

};