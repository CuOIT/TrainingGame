#pragma once
#include"Sprite2D.h"

class StatusBar {
//#define w
public :
	StatusBar(int maxHp,int maxMana,bool isPlayer);
	~StatusBar();

	void SetHp(int hp) {
		m_hp = hp;
		m_hpBar->SetSize(180 * m_hp / m_maxHp,10);
		//m_hpBar->SetPosition(120+ 180 * m_hp / m_maxHp)
	}
	void SetMana(int mana) {
		m_mana = mana;
		m_manaBar->SetSize(180 * m_mana / m_maxMana, 10);
	}
private:
	std::shared_ptr<Sprite2D> m_avatar;
	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<Sprite2D> m_hpBar;
	std::shared_ptr<Sprite2D> m_manaBar;

	int m_maxHp;
	int m_maxMana;
	int m_hp;
	int m_mana;
};