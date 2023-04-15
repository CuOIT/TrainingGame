#pragma once
#include "Text.h"
#include "Sprite2D.h"
#include "GameStateBase.h"
#include "GameButton.h"
#include "GameStateMachine.h"

class Sprite2D;
class Text;
class GameButton;
class SpriteAnimation;
class Level;
class PlayerManager;

class GSLevel : public GameStateBase
{
private:
	std::shared_ptr<Sprite2D>					m_info;
	std::vector<std::shared_ptr<Text>>			m_infoText;
	std::shared_ptr<Sprite2D>					m_background;
	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::list<std::shared_ptr<Text>>			m_listText;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<Level>						m_level;
	std::shared_ptr<PlayerManager>				m_playerManager;
	

public:
	GSLevel();
	~GSLevel();

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
};