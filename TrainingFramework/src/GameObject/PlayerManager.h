#pragma once
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Text.h"
#include "GameButton.h"
#include "Singleton.h"
#include"Entity.h"

class PlayerManager : public Sprite2D, public CSingleton<PlayerManager>
{
private:

	std::list<std::shared_ptr<Sprite2D>>			m_listSprite2D;
	std::shared_ptr<Entity>							m_player;
	std::list<std::shared_ptr<Text>>				m_listText;
	std::list<std::shared_ptr<GameButton>>			m_listButton;
	std::vector<std::shared_ptr<Entity>>			m_listCharacter;
	std::vector<std::shared_ptr<GameButton>>		m_skillList;
	int												m_currentCharacter;
	std::shared_ptr<Sprite2D>			m_info;
	std::vector<std::shared_ptr<Text>>	m_infoText;
public:
	PlayerManager();
	~PlayerManager();
	void Init();
	void Draw();
	void Update(float deltaTime);
	void HandleTouchEvents(float x, float y, bool bIsPressed);
	void HandleMouseMovesEvent(float x, float y);
	std::shared_ptr<Entity>				GetPlayer();

};