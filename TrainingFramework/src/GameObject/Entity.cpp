#include "Entity.h"

//Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
//	std::string name, int maxHealth, int maxMana, int attack, int defense, bool isAlive = true)
//	: Sprite2D(model, shader, texture)
//{
//	m_name = name;
//	m_maxHealth = maxHealth;
//	m_maxMana = maxMana;
//	m_attack = attack;
//	m_defense = defense;
//	m_isAlive = isAlive;
//}

Entity::~Entity()
{

}

int	Entity::GetMaxHealth()
{
	return m_maxHealth;
};

void Entity::SetMaxHealth(int maxHealth)
{
	m_maxHealth = maxHealth;
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

int	Entity::GetCurrentHealth()
{
	return m_currentHealth;
};

void Entity::SetHealth(int health)
{
	if (health > 0)
		m_currentHealth = health;
	else
		m_currentHealth = 0;
}

int	Entity::GetCurrentMana()
{
	return m_currentMana;
};

void Entity::SetMana(int mana)
{
	if (mana > 0)
		m_currentMana = mana;
	else
		m_currentMana = 0;
}

bool Entity::GetIsAlive()
{
	return m_isAlive;
}

void Entity::SetIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

std::string Entity::GetName() 
{
	return m_name;
}

void Entity::SetName(std::string name)
{
	m_name = name;
}

void Entity::TakeDamage(int amount)
{
	int health = m_currentHealth - amount;
	if (health <= 0)
	{
		SetIsAlive(false);
	}
	else
		SetHealth(health);
}

void Entity::AddHealth(int amount)
{
	int health = m_currentHealth + amount;
	if (health > m_maxHealth)
	{
		SetHealth(m_maxHealth);
	}
	else 
		SetHealth(health);
}

void Entity::AddMana(int amount)
{
	int mana = m_currentMana + amount;
	if (mana > m_maxMana)
	{
		SetMana(m_maxMana);
	}
	else
		SetMana(mana);
}
