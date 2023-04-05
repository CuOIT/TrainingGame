#pragma once
#include"Sprite2D.h"
#include"Entity.h"
class StatusBar {
	//#define w
public:
	StatusBar(int maxHp, int maxMana, bool isPlayer);
	~StatusBar();

	void SetHp(int hp);
	void SetMana(int mana);
	void Update(float deltaTime,std::shared_ptr<Entity> entity);
	void Draw();
private:
	std::shared_ptr<Sprite2D> m_avatar;
	std::shared_ptr<Sprite2D> m_statusBarBG;
	std::shared_ptr<Sprite2D> m_hpBar;
	std::shared_ptr<Sprite2D> m_manaBar;

	int x;
	int y;
	bool m_isPlayer;
	int m_maxHp;
	int m_maxMana;
	int m_hp;
	int m_mana;
};