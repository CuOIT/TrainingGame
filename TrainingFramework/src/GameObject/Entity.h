#pragma once
#include"SpriteAnimation.h"
#include"Sprite2D.h"
class Entity : public SpriteAnimation
{
protected:
	int				m_maxHp;
	int				m_maxMana;
	int				m_attack;

	bool			m_isAlive;
	int				m_curHp;
	int				m_curMana;
	int				m_defense;
	bool			m_isAttacking;
	int				m_attackNum;
	std::list<int>	m_poisonList;//stored poison in 3 round;

	std::string	m_name;

public:
	Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
		std::string name, int maxHp, int maxMana, int attack, int defense);

	//Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
	//	std::string name, int maxHealth, int maxMana, int attack, int defense, bool isAlive)
	//	: SpriteAnimation(model, shader, texture,numFrames,numActions,currentAction,frameTime)
	//	,m_name(name),m_maxHealth(maxHealth),m_maxMana(maxMana),m_currentHealth(maxHealth),m_currentMana(0),m_attack(attack),m_defense(defense),m_isAlive(isAlive){};
	~Entity();

	void Update(float deltaTime);
	bool MoveTo(float x, float deltaTime);
	int			GetMaxHp();
	int			GetMaxMana();
	int 		GetAttack();
	int 		GetDefense();
	std::string GetName();
	int			GetCurrentHp();
	int			GetCurrentMana();
	void		Attack(std::shared_ptr<Entity> e, float deltaTime);
	bool		IsAttacking() {
		return m_isAttacking;
	};
	void		SetIsAttack(bool attack) {
			m_isAttacking = attack;
	}
	void		SetAttackNum(int attackNum) {
		m_attackNum = attackNum;
	}
	bool		IsAlive();

	void		SetMaxHp(int maxHp);
	void		SetMaxMana(int maxMana);
	void 		SetHp(int hp);
	void 		SetMana(int mana);
	void 		SetAttack(int attack);
	void		SetDefense(int defense);
	void		SetIsAlive(bool isAlive);
	void		SetName(std::string name);
	int			GetPoison();

	void		TakeDamage(int damage);
	void		TakeDamageOfPoison();
	void		Heal(int hp);
	void		GainMana(int mana);
	void		LostMana(int mana);
	void		Poisoned(int poison);
};