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
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "Here is Guide page", 
														Vector4(1.0f, 0.5f, 0.0f, 1.0f), 2.0f);
	text->Set2DPosition(Vector2(50.0f, 50.0f));
	m_listText.push_back(text);

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
	/*m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}*/
}

void GSGuide::Draw()
{
	/*m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}*/
	for (auto it : m_listText)
	{
		it->Draw();
	}
}