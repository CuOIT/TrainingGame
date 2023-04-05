#pragma once
#include "GameStateBase.h"
#include"GameBoard.h"
#include"GameField.h"
#include"Player.h"
#include"Entity.h"
#include "PauseMenu.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(float x, float y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int m_KeyPress;
	
	bool GetIsPause() { return m_isPause; };
	void SetIsPause(bool isPause) { m_isPause = isPause; };

private:
	std::shared_ptr<GameBoard>	m_gameBoard;
	std::shared_ptr<GameField>	m_gameField;
	std::shared_ptr<Sprite2D>	m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<Piece>	m_piece;
	std::shared_ptr<Entity> m_player;
	std::shared_ptr<Entity> m_enemy;
	std::shared_ptr<PauseMenu> m_pauseMenu;
	bool m_isPause = false;
	
};

