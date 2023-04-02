#pragma once
#include"Entity.h"

class Player : public Entity
{
public:
	Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime,
		std::string name, int maxHealth, int maxMana, int attack, int defense, bool isAlive) :Entity(model, shader, texture, numFrames, numActions, currentAction, frameTime, name, maxHealth, maxMana, attack, defense, isAlive) {};
	~Player();
private:
	int time;
};