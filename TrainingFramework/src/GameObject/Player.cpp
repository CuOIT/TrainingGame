#include"Entity.h"
#include"Player.h"

Player::Player()
{

}

Player::~Player() {

};

Player::Player(std::string name, int maxHealth, int maxMana, int attack, int defense)
{
	m_name = name;
	m_maxHp = maxHealth;
	m_maxMana = maxMana;
	m_attack = attack;
	m_defense = defense;
}