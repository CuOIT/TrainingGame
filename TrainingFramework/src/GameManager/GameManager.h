#pragma once

#include "Entity.h"
#include "GameBoard.h"
#include <map>

enum class Turn
{
	PLAYER_TURN,
	ENEMY_TURN,
	END
};

class GameManager : public CSingleton<GameManager>
{
private:
	Turn						m_turn;
public:
	GameManager() { m_turn = Turn::PLAYER_TURN; };
	~GameManager() {};
	std::map<std::string, int>	CalculatePoint(GameBoard &gameBoard);
	void						SetTurn(Turn turn);
	Turn						GetTurn();
	void						Update(float deltatime, GameBoard& gameBoard, Entity player, Entity enemy);
};