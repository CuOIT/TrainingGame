#pragma once
#include "Entity.h"
#include "GameBoard.h"
class EarthCharacter :public Entity
{
public:
	EarthCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, std::string name, int maxHp, int maxMana, int attack, int defense);

	EarthCharacter();
	~EarthCharacter();
	void UseSkill1() override;
	void UseSkill2()  override;
	void UseSkill3(std::shared_ptr<GameBoard>) override;

};