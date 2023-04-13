#include "GSIntro.h"

GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("intro.tga");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_logo->SetSize(Globals::screenWidth, Globals::screenWidth);
	texture = ResourceManagers::GetInstance()->GetTexture("bg_intro.tga");
	m_bg = std::make_shared<Sprite2D>(model, shader, texture);
	m_bg->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_bg->SetSize(Globals::screenWidth, Globals::screenHeight);
}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSIntro::HandleTouchEvents(float x, float y, bool bIsPressed)
{
}

void GSIntro::HandleMouseMoveEvents(float x, float y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1.5)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_bg->Draw();
	m_logo->Draw();
}
