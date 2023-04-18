#pragma once
#include"SpriteAnimation.h"
#include"Sprite2D.h"
#include"GameButton.h"
#include"Text.h"
#include"GameBoard.h"

#define FIRE 0
#define WATER 1
#define EARTH 2
class Entity : public SpriteAnimation
{
protected:
	//Inherent
	int				m_element;
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

	std::vector<std::shared_ptr<GameButton>> m_skills;
	std::vector<std::vector<std::shared_ptr<Text>>>			 m_detailOfSKills;
	std::shared_ptr<Entity> m_opponent;

	//Effect
	std::list<int>	m_poisonList;//stored poison in 3 round;
	int				m_burnedTurn;//number of turns that be burned
	int				m_freezedTurn;//number of turns that be freezed
	int				m_mutedTurn;//number of turns that can attack
	std::shared_ptr<SpriteAnimation> m_effect;
	std::shared_ptr<SpriteAnimation> m_continousEffect;


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

	int			GetElement();
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
	bool		IsFreezed();
	void		SetFreezed(int);
	void		SetEffect(std::shared_ptr<SpriteAnimation>){};
	void		SetContinousEffect(std::shared_ptr<SpriteAnimation>) {};
	void		SetElement(int element);
	bool		IsBurned();
	void		SetBurned(int);

	bool		IsPoisoned();
	void		SetPoisoned(int);
	bool		IsMuted();
	void		SetMuted(int);

	int			GetMaxHp();
	int			GetMaxMana();
	int 		GetAttack();
	int 		GetDefense();
	std::string GetName();
	int			GetCurrentHp();
	int			GetCurrentMana();
	int			GetFreezed();
	int			GetBurned();
	int			GetMuted();
	std::vector < std::shared_ptr<GameButton>> GetSkillList();
	std::vector<std::shared_ptr<Text>> GetDetailOfSkill(int num);
	std::shared_ptr<SpriteAnimation> GetEffect() {
		return m_effect;
	};
	std::shared_ptr<SpriteAnimation> GetContinousEffect() {
		return m_continousEffect;
	};



	bool		MoveTo(float x, float deltaTime);
	void		Attack(float deltaTime);

	bool		IsAttacking();
	bool		IsAlive();

	int			GetAttackNum();
	int			GetPoison();

	void		TakeDamage(int damage);
	void		TakeDamageOfEffect();
	void		Heal(int hp);
	void		GainMana(int mana);
	void		LostMana(int mana);
	void		Poisoned(int poison);

	  virtual void		UseSkill1(){};
	  virtual void		UseSkill2(){};
	  virtual void		UseSkill3(std::shared_ptr<GameBoard>){};

};