#pragma once
#include "Sprite2D.h"
#include "Text.h"
#include "GameButton.h"
#include "Singleton.h"

class Level : public Sprite2D, public CSingleton<Level>
{
private:
	std::list<std::shared_ptr<Sprite2D>>		m_listSprite2D;
	std::list<std::shared_ptr<Text>>			m_listText;
	std::vector<std::shared_ptr<GameButton>>		m_listButton;
	int m_numPassedLevel = 0;
	int m_currentLevel = 0;
public:
	Level();
	~Level();
	void Init();
	void Draw();
	void Update(float deltaTime);
	void HandleTouchEvents(float x, float y, bool bIsPressed);
	
	void SetSelectedLevel(int level) { m_currentLevel = level; };
	int GetSelectedLevel() { return m_currentLevel; };
	void SetNumPassedLevel(int level) { m_numPassedLevel = level; };
	int GetNumPassedLevel() { return m_numPassedLevel; };

};