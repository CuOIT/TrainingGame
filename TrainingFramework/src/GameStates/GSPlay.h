#pragma once
#include "GameStateBase.h"
#include"GameBoard.h"
#include"GameField.h"
#include"Player.h"
#include"Entity.h"
#include "PauseMenu.h"
#include "EndGameMenu.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay(std::shared_ptr<Entity> p, int currentLevel);

	GSPlay();

	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	std::shared_ptr<Entity> GetPlayer() {
		return m_player;
	}
	std::shared_ptr<Entity> GetEnemy() {
		return m_enemy;
	}

	int GetCurrentLevel() {
		return m_currentLevel;
	};
	void SetCurrentLevel(int level) {
		m_currentLevel = level;
	};

	void	HandleMouseMoveEvents(float x, float y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int m_KeyPress;
	
	bool GetIsPause() { return m_isPause; };
	void SetIsPause(bool isPause) { m_isPause = isPause; };

private:
	int										m_currentLevel;
	std::shared_ptr<Entity>					m_player;
	std::shared_ptr<Entity>					m_enemy;
	std::shared_ptr<GameBoard>				m_gameBoard;
	std::shared_ptr<GameField>				m_gameField;
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<PauseMenu>				m_pauseMenu;
	std::shared_ptr<EndGameMenu>			m_endGameMenu;
	bool m_isPause = false;
};

