#include "GameManager.h"
#include "GameBoard.h"
#include <set>
#include <algorithm>
#include "GameStates/GameStateMachine.h"

std::map<std::string, int> GameManager::CalculatePoint (GameBoard &gameBoard)
{
	std::set<std::pair<int, int>> listOfMatch = gameBoard.GetMatchList();
	
	int healthMatch = 0, manaMatch = 0, attackMatch = 0, defenseMatch = 0;
	std::map<std::string, int> point;
	point["health"] = healthMatch;
	point["mana"] = manaMatch;
	point["attack"] = attackMatch;
	point["defense"] = defenseMatch;

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
				healthMatch++;
				break;
			case PieceType::Mana:
				manaMatch++;
				break;
			case PieceType::Sword:
				attackMatch++;
				break;
			case PieceType::Shield:
				defenseMatch++;
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
		}
		if (point["defense"] > 0)
		{
			player.SetDefense(point["defense"] + player.GetDefense());
		}
		if (point["attack"] > 0)
		{
			enemy.TakeDamage(point["attack"]);
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
