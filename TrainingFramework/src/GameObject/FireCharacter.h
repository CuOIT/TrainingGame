#pragma once
#include "Entity.h"
#include "GameBoard.h"
class FireCharacter :public Entity
{
public:
	FireCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, std::string name, int maxHp, int maxMana, int attack, int defense) :
		Entity(model, shader, texture, numFrames, numActions, currentAction, frameTime, name, maxHp, maxMana, attack, defense) {};

	FireCharacter();
	~FireCharacter();
	void UseSkill1();
	void UseSkill2();
	void UseSkill3(std::shared_ptr<GameBoard>);

};
