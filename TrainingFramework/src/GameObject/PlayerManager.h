#pragma once
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Text.h"
#include "GameButton.h"
#include "Singleton.h"

class PlayerManager : public Sprite2D, public CSingleton<PlayerManager>
{
private:

	std::list<std::shared_ptr<Sprite2D>>			m_listSprite2D;
	std::list<std::shared_ptr<SpriteAnimation>>		m_listAnimation;
	std::list<std::shared_ptr<Text>>				m_listText;
	std::list<std::shared_ptr<GameButton>>			m_listButton;

public:
	PlayerManager();
	~PlayerManager();
	void Init();
	void Draw();
	void Update(float deltaTime);
	void HandleTouchEvents(float x, float y, bool bIsPressed);

};