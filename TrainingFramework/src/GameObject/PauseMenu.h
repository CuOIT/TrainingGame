#pragma once
#include "Text.h"
#include "Sprite2D.h"
#include "GameButton.h"
#include <list>

class GSPlay;
class PauseMenu : public Sprite2D
{
private:
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Sprite2D>				m_bgPause;
	std::shared_ptr<Sprite2D>				m_pauseHeader;
	std::shared_ptr<GameButton>				m_btnSoundOn;
	std::shared_ptr<GameButton>				m_btnSoundOff;
	std::list<std::shared_ptr<Text>>		m_listText;
	bool m_isPlaySound = true;
public:
	PauseMenu(GSPlay *gs);
	~PauseMenu();

	void Init(GSPlay* gs);
	void Draw();
	void Update(float deltaTime);
	void HandleTouchEvents(int x, int y, bool isPressed);
};