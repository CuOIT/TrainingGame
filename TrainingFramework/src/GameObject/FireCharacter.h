#pragma once
#include "Entity.h"
#include "GameBoard.h"
class FireCharacter :public Entity
{
public:
	FireCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, std::string name, int maxHp, int maxMana, int attack, int defense);
	
	FireCharacter();
	~FireCharacter();
	void Attack(float);
	void UseSkill1() override;
	void UseSkill2() override;
	void UseSkill3(std::shared_ptr<GameBoard>) override;
private:
	bool m_power;

};
