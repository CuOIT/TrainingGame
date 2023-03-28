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
	int			m_currentHP;
	int			m_currentMana;

	std::string	m_name;

public:
	Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
		: Sprite2D(model, shader, texture) {};
	~Entity();

	int			GetMaxHP();
	int			GetMaxMana();
	int 		GetAttack();
	int 		GetDefense();

	int			GetCurrentHP();
	int			GetCurrentMana();
	bool		GetIsAlive();
	 
	void		SetMaxHP(int maxHP);
	void		SetMaxMana(int maxMana);
	void 		SetCurrentHP(int curHP);
	void 		SetCurrentMana(int curMana);
	void 		SetAttack(int curAtt);
	void		SetDefense(int curDef);
	void		SetIsAlive(bool isAlive);

	void		TakeDamage(int damage);

};