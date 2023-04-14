#pragma once
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Text.h"
#include "GameButton.h"
#include "Singleton.h"
#include "Player.h"

class PlayerManager : public Sprite2D, public CSingleton<PlayerManager>
{
private:

	std::list<std::shared_ptr<Sprite2D>>			m_listSprite2D;
	std::vector<std::shared_ptr<SpriteAnimation>>		m_listAnimation;
	std::vector<std::shared_ptr<Text>>				m_listText;
	std::list<std::shared_ptr<GameButton>>			m_listButton;
	std::shared_ptr<Player>							m_selectedPlayer;
	std::vector<std::shared_ptr<Player>>			m_listPlayer;
	bool m_isSwitchPlayer = false;
public:
	PlayerManager();
	~PlayerManager();
	void Init();
	void Draw();
	void Update(float deltaTime);
	void HandleTouchEvents(float x, float y, bool bIsPressed);

	std::shared_ptr<Player> GetSelectedPlayer() { return m_selectedPlayer; };
};