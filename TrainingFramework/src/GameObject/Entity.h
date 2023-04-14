#pragma once
#include"SpriteAnimation.h"
#include"Sprite2D.h"
#include"GameBoard.h"
class Entity : public SpriteAnimation
{
protected:
	//Inherent
	int				m_type;
	int				m_maxHp;
	int				m_maxMana;
	int				m_attack;
	std::string		m_name;

	//mutable
	bool			m_isAlive;
	int				m_curHp;
	int				m_curMana;
	int				m_defense;
	bool			m_isAttacking;
	int				m_attackNum;
	std::shared_ptr<Entity> m_opponent;

	//Effect
	std::list<int>	m_poisonList;//stored poison in 3 round;
	bool			m_isPoisoned;
	bool			m_isFreezed;
	bool			m_isBurned;

	//For drawing
	float			m_standbyTime;

public:
	Entity();

	Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
		std::string name, int maxHp, int maxMana, int attack, int defense);

	//Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
	//	std::string name, int maxHealth, int maxMana, int attack, int defense, bool isAlive)
	//	: SpriteAnimation(model, shader, texture,numFrames,numActions,currentAction,frameTime)
	//	,m_name(name),m_maxHealth(maxHealth),m_maxMana(maxMana),m_currentHealth(maxHealth),m_currentMana(0),m_attack(attack),m_defense(defense),m_isAlive(isAlive){};
	~Entity();

	void		Update(float deltaTime);

	void		SetMaxHp(int maxHp);
	void		SetMaxMana(int maxMana);
	void		SetIsAttack(bool attack);
	void		SetIsAlive(bool alive);
	void		SetAttackNum(int attackNum);
	void 		SetHp(int hp);
	void 		SetMana(int mana);
	void 		SetAttack(int attack);
	void		SetDefense(int defense);
	void		SetName(std::string name);
	void		SetOpponent(std::shared_ptr<Entity> op);
	void		SetFreezed(bool);


	bool		IsBurned();
	void		SetBurned(bool isBurned);

	bool		IsPoisoned();
	void		SetPoisoned(bool isPoisoned);


	int			GetMaxHp();
	int			GetMaxMana();
	int 		GetAttack();
	int 		GetDefense();
	std::string GetName();
	int			GetCurrentHp();
	int			GetCurrentMana();

	bool		MoveTo(float x, float deltaTime);
	void		Attack(float deltaTime);

	bool		IsAttacking();
	bool		IsAlive();
	bool		IsFreezed();

	int			GetAttackNum();
	int			GetPoison();

	void		TakeDamage(int damage);
	void		TakeDamageOfPoison();
	void		Heal(int hp);
	void		GainMana(int mana);
	void		LostMana(int mana);
	void		Poisoned(int poison);

	  void		UseSkill1();
	  void		UseSkill2();
	  void		UseSkill3(std::shared_ptr<GameBoard>);

};