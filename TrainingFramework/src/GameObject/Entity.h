#pragma once
#include"Sprite2D.h"

class Entity : public Sprite2D 
{
protected:
	int			m_maxHealth;
	int			m_maxMana;
	int			m_attack;
	int			m_defense;

	bool		m_isAlive;
	int			m_currentHealth;
	int			m_currentMana;

	std::string	m_name;

public:
	Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, 
		std::string name, int maxHealth, int maxMana, int attack, int defense, bool isAlive)
		: Sprite2D(model, shader, texture) {};
	~Entity();

	int			GetMaxHealth();
	int			GetMaxMana();
	int 		GetAttack();
	int 		GetDefense();
	std::string GetName();
	int			GetCurrentHealth();
	int			GetCurrentMana();
	bool		GetIsAlive();
	 
	void		SetMaxHealth(int maxHealth);
	void		SetMaxMana(int maxMana);
	void 		SetHealth(int health);
	void 		SetMana(int mana);
	void 		SetAttack(int attack);
	void		SetDefense(int defense);
	void		SetIsAlive(bool isAlive);
	void		SetName(std::string name);

	void		TakeDamage(int damage);
	void		AddHealth(int amount);
	void		AddMana(int amount);
};