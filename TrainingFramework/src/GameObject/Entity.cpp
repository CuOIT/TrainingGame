#include "Entity.h"

Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
	std::string name, int maxHealth, int maxMana, int attack, int defense, bool isAlive = true)
	: Sprite2D(model, shader, texture)
{
	m_name = name;
	m_maxHealth = maxHealth;
	m_maxMana = maxMana;
	m_attack = attack;
	m_defense = defense;
	m_isAlive = isAlive;
}

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

int	Entity::GetCurrentHealth()
{
	return m_currentHealth;
};

void Entity::SetHealth(int health)
{
	m_currentHealth = health;
}

int	Entity::GetCurrentMana()
{
	return m_currentMana;
};

void Entity::SetMana(int mana)
{
	m_currentMana = mana;
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

void Entity::Heal(int amount)
{
	int health = m_currentHealth + amount;
	if (health > m_maxHealth)
	{
		SetHealth(m_maxHealth);
	}
	else 
		SetHealth(health);
}