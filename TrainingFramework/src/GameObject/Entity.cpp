#include "Entity.h"
#include"ResourceManagers.h"
#include"GameButton.h"
Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture
	, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
	std::string name, int maxHp, int maxMana, int attack, int defense)
	: SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
	, m_name(name), m_maxHp(maxHp), m_maxMana(maxMana), m_curHp(maxHp), m_curMana(0)
	, m_attack(attack), m_defense(defense), m_isAlive(true) {
	m_attackNum = 0;
	m_standbyTime = 0;

	auto model2 = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader2 = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture2 = ResourceManagers::GetInstance()->GetTexture("");
	m_skills.push_back(std::make_shared<GameButton>(model2,shader2,texture2));
	m_skills.push_back(std::make_shared<GameButton>(model2, shader2, texture2));
	m_skills.push_back(std::make_shared<GameButton>(model2, shader2, texture2));
	m_skills[0]->SetSize(50, 50);
	m_skills[1]->SetSize(50, 50);
	m_skills[2]->SetSize(50, 50);

	m_poisonList.push_back(0);
	m_poisonList.push_back(0);
	m_poisonList.push_back(0);
	m_isAttacking = false;

};

Entity::Entity()
{

}

Entity::~Entity()
{

}

bool		Entity::IsAttacking() {
	return m_isAttacking;
};

void		Entity::SetIsAttack(bool attack) {
	m_isAttacking = attack;
}
void		Entity::SetAttackNum(int attackNum) {
	m_attackNum = attackNum;
}
void Entity::Update(float deltaTime) {
	SpriteAnimation::Update(deltaTime);
	//m_currentTime += deltaTime;
	//if (m_currentTime >= m_frameTime)
	//{
	//	m_currentFrame++;
	//	if (m_currentFrame >= m_numFrames) {
	//		if (!IsAlive()) {
	//			m_currentFrame = m_numFrames - 1;
	//		}else
	//			m_currentFrame = 0;
	//	}
	//	m_currentTime -= m_frameTime;
	//}
	if (m_attackNum > 0) {
		Attack(deltaTime);
	}
}
bool		Entity::IsFreezed() {
	return m_isFreezed;
};
void		Entity::SetFreezed(bool isFreezed) {
	m_isFreezed= isFreezed;
};

bool		Entity::IsBurned() {
	return m_isBurned;
};
void		Entity::SetBurned(bool isBurned) {
	m_isBurned = isBurned;
};

bool		Entity::IsPoisoned() {
	return m_isPoisoned;
};
void		Entity::SetPoisoned(bool isPoisoned) {
	m_isPoisoned = isPoisoned;
};

int Entity::GetAttackNum() {
	return m_attackNum;
}

std::vector < std::shared_ptr<GameButton>> Entity::GetSkillList() {
	return m_skills;
}
std::vector<std::shared_ptr<Text>> Entity::GetDetailOfSkill(int num) {
	return m_detailOfSKills[num];
};


void Entity::Attack(float deltaTime) {
		if (m_isAttacking) {
			MoveTo(m_opponent->Get2DPosition().x, deltaTime);
			if (abs(Get2DPosition().x - m_opponent->Get2DPosition().x) <50) {
				if(m_standbyTime==0) 
					SetTexture(ResourceManagers::GetInstance()->GetTexture(m_name + "_attack.tga"), false);
				m_standbyTime += deltaTime;
				if (m_standbyTime > 0.29) {
					m_opponent->TakeDamage(m_attack*m_attackNum);
					m_isAttacking = false;
					m_standbyTime = 0;
				}
				 //SetTexture(ResourceManagers::GetInstance()->GetTexture(m_name+"_idle.tga"));
			}
		}
		else if(m_isLooped==true) {
			MoveTo(Globals::screenWidth - m_opponent->Get2DPosition().x, deltaTime);
		}
		if (Get2DPosition().x == Globals::screenWidth - m_opponent->Get2DPosition().x) m_attackNum = 0;
	
}
bool Entity::MoveTo(float x, float deltaTime) {
	int s = (x - Get2DPosition().x) * deltaTime * 3;
	if (abs(s) < 1) {
	if ((x - Get2DPosition().x)>0) s = 1;
	else s = -1;
	}
	Set2DPosition((int)(Get2DPosition().x + s), Get2DPosition().y);
	if (abs(Get2DPosition().x - x)< 2) {
		Set2DPosition(x, GetPosition().y);
		return true;
	}
	return false;

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

void Entity::SetIsAlive(bool alive) {
	m_isAlive = alive;
	if (!alive) {
		SetTexture(ResourceManagers::GetInstance()->GetTexture(m_name+"_dead.tga"),false);
		SetLastTexture(ResourceManagers::GetInstance()->GetTexture(m_name + "_dead2.tga"));
	}


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
void Entity::SetOpponent(std::shared_ptr<Entity> op) {
	m_opponent = op;
};

void Entity::TakeDamage(int damage)
{
	SetTexture(ResourceManagers::GetInstance()->GetTexture(GetName() + "_hurt.tga"), false);
	if (damage > m_defense) {
		m_defense = 0;
		damage -= m_defense;
		int curHp = m_curHp - damage;
		if (curHp <= 0)
		{
			SetHp(0);
			if (IsAlive())
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
	int curHp = m_curHp - poison;
	if (curHp <= 0)
	{
		SetHp(0);
		if(IsAlive())
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
	int curMana = m_curMana + mana;
	SetMana(curMana > m_maxMana ? m_maxMana : curMana);
}
void Entity::LostMana(int mana) {
	int curMana = m_curMana - mana;
	SetMana(curMana < 0 ? 0 : curMana);
}
void Entity::Poisoned(int poison) {
	m_poisonList.back() += poison;
}