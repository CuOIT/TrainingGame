#include "GSMenu.h"
#include "Camera.h"
GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_listText(std::list<std::shared_ptr<Text>>{})
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// bg button
	texture = ResourceManagers::GetInstance()->GetTexture("bg_btn.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f - 150.0f);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f + 50.0f);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	// text for btn
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "Play", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 2.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 50.0f, Globals::screenHeight / 2.0f - 135.0f));
	m_listText.push_back(text);
	
	text = std::make_shared<Text>(shader, font, "Quit", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 2.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 50.0f, Globals::screenHeight / 2.0f + 60.0f));
	m_listText.push_back(text);

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	//font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");
	text = std::make_shared<Text>(shader, font, "Magic Battle", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	text->Set2DPosition(Vector2(60, 200));
	m_listText.push_back(text);

	std::string name = "gravity_fall_theme_sound.wav";
	ResourceManagers::GetInstance()->PlaySound(name,true);
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
	ResourceManagers::GetInstance()->StopSound("gravity_fall_theme_sound.wav");
}

void GSMenu::Resume()
{
	std::string name = "gravity_fall_theme_sound.wav";

	ResourceManagers::GetInstance()->PlaySound(name, true);
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(float x, float y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
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
