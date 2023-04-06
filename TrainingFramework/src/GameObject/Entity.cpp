#include "Entity.h"

Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture
	, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
	std::string name, int maxHp, int maxMana, int attack, int defense)
	: SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
	, m_name(name), m_maxHp(maxHp), m_maxMana(maxMana), m_curHp(maxHp), m_curMana(0)
	, m_attack(attack), m_defense(defense), m_isAlive(true) {
	m_poisonList.push_back(0);
	m_poisonList.push_back(0);
	m_poisonList.push_back(0);

};
Entity::~Entity()
{

}

int	Entity::GetMaxHp()
{
	return m_maxHp;
};

void Entity::SetMaxHp(int maxHp)
{
	m_maxHp = maxHp;
}

int	Entity::GetMaxMana()
{
	return m_maxMana;
};

void Entity::SetMaxMana(int maxMana)
{
	m_maxMana = maxMana;
}

int	Entity::GetAttack()
{
	return m_attack;
};

void Entity::SetAttack(int attack)
{
	if (attack > 0)
		m_attack = attack;
	else
		m_attack = 1;
}

int	Entity::GetDefense()
{
	return m_defense;
};

void Entity::SetDefense(int defense)
{
	if (defense > 0)
		m_defense = defense;
	else
		m_defense = 0;
}

int	Entity::GetCurrentHp()
{
	return m_curHp;
};

void Entity::SetHp(int hp)
{
	m_curHp = hp;
}

int	Entity::GetCurrentMana()
{
	return m_curMana;
};

void Entity::SetMana(int mana)
{
	m_curMana = mana;
}

bool Entity::IsAlive()
{
	return m_isAlive;
}

void Entity::SetIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

int Entity::GetPoison() {
	int poison = 0;
	for (auto x : m_poisonList) {
		poison += x;
	}
	return poison;
}
std::string Entity::GetName()
{
	return m_name;
}

void Entity::SetName(std::string name)
{
	m_name = name;
}

void Entity::TakeDamage(int damage)
{
	if (damage > m_defense) {
		m_defense = 0;
		damage -= m_defense;
		int curHp = m_curHp - damage;
		if (curHp <= 0)
		{
			SetHp(0);
			SetIsAlive(false);
		}
		else
			SetHp(curHp);
	}
	else {
		m_defense -= damage;
	}
}
void Entity::TakeDamageOfPoison()
{
	int poison = 0;
	for (auto x : m_poisonList) {
		poison += x;
	}
	poison *= 10;
	std::cout << this->GetName() << " take POISON : " << poison << std::endl;
	int curHp = m_curHp - poison;
	if (curHp <= 0)
	{
		SetHp(0);
		SetIsAlive(false);
	}
	else
		SetHp(curHp);
	m_poisonList.pop_front();
	m_poisonList.push_back(0);
}

void Entity::Heal(int hp)
{
	int curHp = m_curHp + hp;
	SetHp(curHp > m_maxHp ? m_maxHp : curHp);
}
void Entity::GainMana(int mana) {
	int curMana = m_curMana + 10 * mana;
	SetMana(curMana > m_maxMana ? m_maxMana : curMana);
}
void Entity::LostMana(int mana) {
	int curMana = m_curMana - mana;
	SetMana(curMana < 0 ? 0 : curMana);
}
void Entity::Poisoned(int poison) {
	m_poisonList.back() += poison;
}