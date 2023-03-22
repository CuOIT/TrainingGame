#pragma once
#include"Sprite2D.h"

class Entity : public Sprite2D 
{
protected:
	int			m_maxHP;
	int			m_maxMana;
	int			m_attack;
	int			m_defense;

	bool		m_isAlive;
	int			m_CurrentHP;
	int			m_CurrentMana;

	std::string	m_name;

public:
	int			getMaxHP();
	int			getMaxMana();
	int 		getAttack();
	int 		getDefense();

	int			getCurrentHP();
	int			getCurrentMana();
	bool		getIsAlive();
	 
	void		setMaxHP();
	void		setMaxMana();
	void 		setCurrentHP();
	void 		setCurrentMana();
	void 		setAttack();
	void		setDefense();
	void		setIsAlive();
};