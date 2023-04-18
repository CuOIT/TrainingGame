#pragma once
#include "BaseObject.h"
#include"Texture.h"
class SpriteAnimation : public BaseObject
{
protected:
	GLint			m_iHeight;
	GLint			m_iWidth;
	GLint			m_numFrames;
	GLint			m_currentFrame;
	GLfloat			m_frameTime;
	GLfloat			m_currentTime;
	GLint			m_numActions;
	GLint			m_currentAction;//index from 0 to m_numActions-1
	std::shared_ptr<Texture>	m_lastTexture;
	bool			m_isLooped;

public:
	SpriteAnimation();
	SpriteAnimation(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~SpriteAnimation();

	void		Init() override;
	void		Draw() final;
	void		Update(GLfloat deltatime) override;

	void		SetLoop(bool isLooped);
	void		SetTexture(std::shared_ptr<Texture> texture,bool isLooped);
	void		SetNumFrames(int);
	void		SetLastTexture(std::shared_ptr<Texture> texture);
	void		Set2DPosition(GLfloat x, GLfloat y);
	void		SetRotation(Vector3 rotation);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);
};

