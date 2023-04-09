#include "GSLevel.h"
#include "Camera.h"
#include "Player.h"
#include "Level.h"
#include "SaveData.h"

GSLevel::GSLevel()
{
}

GSLevel::~GSLevel()
{	
}

void GSLevel::Init()
{
	
	// bg
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.tga");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.0f, Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// bg for menu
	texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f - 200.0f, Globals::screenHeight / 2.0f);
	sprite->SetSize(Globals::screenWidth / 2.0 - 20, Globals::screenHeight / 2);
	m_listSprite2D.push_back(sprite);

	// header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition((float)Globals::screenWidth / 2.0f - 200.0f, (float)Globals::screenHeight / 2.0f - 220.0f);
	sprite->SetSize(250.0f, 75.0f);
	m_listSprite2D.push_back(sprite);

	// button
	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_home.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50.0f, 50.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		SaveData::GetInstance()->SaveLevel(Level::GetInstance()->GetNumPassedLevel());
		});
	m_listButton.push_back(button);

	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "PLAYER", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 250.0f, (float)Globals::screenHeight / 2.0f - 210.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "NAME: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(80.0f, 400.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "HP: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(80.0f, 620.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "MP: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(80.0f, 650.0f));
	m_listText.push_back(text);

	// level
	m_level = Level::GetInstance();

	// animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("warrior3_auto_x24.tga");
	std::shared_ptr<Player> player = std::make_shared<Player>(model, shader, texture, 8, 6, 4, 0.05f, "Player", 200, 200, 2, 0);
	player->Set2DPosition(220, 440);
	player->SetSize(250, 250);
	m_listAnimation.push_back(player);
}

void GSLevel::Exit()
{
}

void GSLevel::Pause()
{
}

void GSLevel::Resume()
{
}

void GSLevel::HandleEvents()
{

}

void GSLevel::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSLevel::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
	m_level->HandleTouchEvents(x, y, bIsPressed);
}

void GSLevel::HandleMouseMoveEvents(float x, float y)
{

}

void GSLevel::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
}

void GSLevel::Draw()
{
	m_background->Draw();
	m_level->Draw();
	for (auto it : m_listSprite2D)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}