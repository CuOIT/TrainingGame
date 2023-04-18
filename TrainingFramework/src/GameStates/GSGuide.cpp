#include "GSGuide.h"
#include "Camera.h"

GSGuide::GSGuide() 
{
}

GSGuide::~GSGuide()
{
}

void GSGuide::Init()
{
	// bg
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("guide.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button
	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_home.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50.0f, 50.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


}

void GSGuide::Exit()
{
}


void GSGuide::Pause()
{
}

void GSGuide::Resume()
{
}

void GSGuide::HandleEvents()
{
}

void GSGuide::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSGuide::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSGuide::HandleMouseMoveEvents(float x, float y)
{
}

void GSGuide::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSGuide::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}