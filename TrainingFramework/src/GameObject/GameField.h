#pragma once
#include"Entity.h"
#include"GameButton.h"
#include"Player.h"
#include"Text.h"
#include"GameBoard.h"
#include"StatusBar.h"
#include<queue>

class GameField {
public:
	enum Phase {
		BEGIN_PHASE,
		BASE_PHASE,
		SWAP_PHASE,
		DESTROY_PHASE,
		REFILL_PHASE,
		END_PHASE
	};

	GameField() {};
	~GameField();
	GameField(std::shared_ptr<Entity> player, std::shared_ptr<Entity> enermy);
	void Init(std::shared_ptr<Entity> player, std::shared_ptr<Entity> enermy);

	void HandleClick(float x, float y,bool isPressed);
	void HandleMouseMoveEvents(float x, float y);
	void Update(float deltaTime);

	void								Calculate(std::vector<int> pieceList,bool isPlayer);
	void								SetPhase(Phase phase);
	Phase								GetPhase();
	void								BotMove();
	void Draw();
	
private:
	bool								m_currentTurn;
	std::shared_ptr<Sprite2D>			m_turnPoint;
	Phase								m_phase;
	float								m_standbyTime;
	std::shared_ptr<Sprite2D>			m_boardMenu;
	std::shared_ptr<Sprite2D>			m_info;
	std::vector<std::shared_ptr<Text>>	m_infoText;


	std::vector<std::shared_ptr<GameButton>>m_skillButtonList;
	std::vector<std::pair<int, int>>	m_click;
	std::vector<int>				m_pieceList;
	std::shared_ptr<Entity>				m_player;
	std::shared_ptr<StatusBar>			m_PStatusBar;
	std::shared_ptr<StatusBar>			m_EStatusBar;
	std::shared_ptr<Entity>				m_enemy;
	std::shared_ptr<GameBoard>			m_gameBoard;
	std::queue<bool>					m_turn;

};