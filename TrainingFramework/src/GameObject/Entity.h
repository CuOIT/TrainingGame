#pragma once
#include"SpriteAnimation.h"
#include"Sprite2D.h"
class Entity : public SpriteAnimation 
{
protected:
	int			m_maxHealth;
	int			m_maxMana;
	int			m_attack;
	int			m_defense;

	bool		m_isAlive;
	int			m_currentHealth;
	int			m_currentMana;

	Sprite2D	m_hpBar;
	Sprite2D	m_manaBar;
	std::string	m_name;

public:
	Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
		std::string name, int maxHealth, int maxMana, int attack,int defense);

	//Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
	//	std::string name, int maxHealth, int maxMana, int attack, int defense, bool isAlive)
	//	: SpriteAnimation(model, shader, texture,numFrames,numActions,currentAction,frameTime)
	//	,m_name(name),m_maxHealth(maxHealth),m_maxMana(maxMana),m_currentHealth(maxHealth),m_currentMana(0),m_attack(attack),m_defense(defense),m_isAlive(isAlive){};
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
	void		Heal(int amount);
};