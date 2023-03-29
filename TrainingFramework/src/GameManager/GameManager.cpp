#include "GameManager.h"
#include "GameBoard.h"
#include <set>
#include <algorithm>
#include "GameStates/GameStateMachine.h"

std::map<std::string, int> GameManager::CalculatePoint (GameBoard &gameBoard)
{
	std::set<std::pair<int, int>> listOfMatch = gameBoard.GetMatchList();
	
	std::map<std::string, int> point;
	point["health"] = 0;
	point["mana"] = 0;
	point["attack"] = 0;
	point["defense"] = 0;

	if (gameBoard.HasAnMatch())
	{
		for (auto it : listOfMatch)
		{
			int row = it.first;
			int col = it.second;
			PieceType type = gameBoard.m_board[row][col]->GetType();

			switch (type)
			{
			case PieceType::HP:
				point["health"]++;
				break;
			case PieceType::Mana:
				point["mana"] = 0;
				break;
			case PieceType::Sword:
				point["attack"] = 0;
				break;
			case PieceType::Shield:
				point["defense"] = 0;
				break;
			}
		}
	}
	return point;
}

void GameManager::Update(float deltatime, GameBoard &gameboard, Entity player, Entity enemy)
{
	std::map<std::string, int> point;

	Phase phase = gameboard.getPhase();
	if (phase == Phase::DESTROY_PHASE)
	{
		point = CalculatePoint(gameboard);
	}

	Turn turn = GetTurn();
	switch (turn)
	{
	case Turn::PLAYER_TURN:
		if(point["health"] > 0)
		{
			player.AddHealth(point["health"]);
			std::cout << "health: " + player.GetCurrentHealth() << std::endl;
		}
		if (point["mana"] > 0)
		{
			player.AddMana(point["mana"]);
			std::cout << "mana: " + player.GetCurrentMana() << std::endl;
		}
		if (point["defense"] > 0)
		{
			player.SetDefense(point["defense"] + player.GetDefense());
			std::cout << "defense: " + player.GetDefense() << std::endl;
		}
		if (point["attack"] > 0)
		{
			enemy.TakeDamage(point["attack"]);
			std::cout << "attack" << std::endl;
		}
		if (!player.GetIsAlive())
			SetTurn(Turn::END);
		if (gameboard.m_isChangeTurn)
			SetTurn(Turn::ENEMY_TURN);
		break;

	case Turn::ENEMY_TURN:
		if (point["health"] > 0)
		{
			enemy.AddHealth(point["health"]);
		}
		if (point["mana"] > 0)
		{
			enemy.AddMana(point["mana"]);
		}
		if (point["defense"] > 0)
		{
			enemy.SetDefense(point["defense"] + enemy.GetDefense());
		}
		if (point["attack"] > 0)
		{
			player.TakeDamage(point["attack"]);
		}
		if (!enemy.GetIsAlive())
			SetTurn(Turn::END);
		if (gameboard.m_isChangeTurn)
			SetTurn(Turn::PLAYER_TURN);
		break;

	case Turn::END:
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		break;
	}	
	
}


void GameManager::SetTurn(Turn turn)
{
	m_turn = turn;
}

Turn GameManager::GetTurn()
{
	return m_turn;
}
