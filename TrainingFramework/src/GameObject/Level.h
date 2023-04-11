#pragma once
#include "Sprite2D.h"
#include "Text.h"
#include "GameButton.h"
#include "Singleton.h"

class Level : public Sprite2D, public CSingleton<Level>
{
private:
	int m_level;
	bool m_isPassed;
	bool m_isEndGame = false;
	bool m_isPlayerWin = true;
	std::list<std::shared_ptr<Sprite2D>>		m_listSprite2D;
	std::list<std::shared_ptr<Text>>			m_listText;
	std::vector<std::shared_ptr<GameButton>>		m_listButton;
	int m_numPassedLevel = 0;
	int m_currentLevel = 1;
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
	void SetIsEndGame(bool isEndGame) { m_isEndGame = isEndGame; };
	bool GetIsEndGame() { return m_isEndGame; };
	bool GetIsPlayerWin() { return m_isPlayerWin; };
	void SetIsPlayerWin(bool isPlayerWin) { m_isPlayerWin = isPlayerWin; };
};