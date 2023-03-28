#include "Entity.h"

Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{

}

Entity::~Entity()
{

}

int	Entity::GetMaxHP()
{
	return m_maxHP;
};

void Entity::SetMaxHP(int maxHP)
{
	m_maxHP = maxHP;
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
	m_attack = attack;
}

int	Entity::GetDefense()
{
	return m_defense;
};

void Entity::SetDefense(int defense)
{
	m_defense = defense;
}

int	Entity::GetCurrentHP()
{
	return m_currentHP;
};

void Entity::SetCurrentHP(int curHP)
{
	m_currentHP = curHP;
}

int	Entity::GetCurrentMana()
{
	return m_currentMana;
};

void Entity::SetCurrentMana(int curMana)
{
	m_currentMana = curMana;
}

bool Entity::GetIsAlive()
{
	return m_isAlive;
}

void Entity::SetIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

void Entity::TakeDamage(int damage)
{
	int iHP = m_currentHP - damage;
	if (iHP > 0)
	{
		SetCurrentHP(iHP);
	}
	else
	{
		SetCurrentHP(0);
	}
}