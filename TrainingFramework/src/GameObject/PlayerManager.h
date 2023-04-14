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
	std::vector<std::shared_ptr<Entity>>				m_listCharacter;
	int												m_currentCharacter;
public:
	PlayerManager();
	~PlayerManager();
	void Init();
	void Draw();
	void Update(float deltaTime);
	void HandleTouchEvents(float x, float y, bool bIsPressed);
	std::shared_ptr<Entity>				GetPlayer();

};