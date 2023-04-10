#include "Level.h"
#include "ResourceManagers.h"
#include "SaveData.h"
#include "GameStates/GameStateMachine.h"

Level::Level() : m_level(0)
{
	Init();
}

Level::~Level()
{
}

void Level::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// bg
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f + 200.0f, Globals::screenHeight / 2.0f);
	sprite->SetSize(Globals::screenWidth / 2.0 - 20, Globals::screenHeight / 2);
	m_listSprite2D.push_back(sprite);

	// header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition((float)Globals::screenWidth / 2.0f + 200.0f, (float)Globals::screenHeight / 2.0f - 220.0f);
	sprite->SetSize(250.0f, 75.0f);
	m_listSprite2D.push_back(sprite);

	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");

	// btn
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int curLevel = i * 4 + j + 1;
			shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			std::shared_ptr<GameButton> button;
			if (curLevel <= m_numPassedLevel + 1)
			{
				texture = ResourceManagers::GetInstance()->GetTexture("btn_level.tga");
				button = std::make_shared<GameButton>(model, shader, texture);
				button->SetOnClick([this, curLevel]() {
					GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
					this->SetSelectedLevel(curLevel);
					});
			}
			else
			{
				texture = ResourceManagers::GetInstance()->GetTexture("btn_level_unclear.tga");
				button = std::make_shared<GameButton>(model, shader, texture);
				button->SetOnClick([]() {

					});
			}
			button->Set2DPosition(475 + j * 85.0f, 360.0f + i * 90.0f);
			button->SetSize(70, 70);
			m_listButton.push_back(button);

			shader = ResourceManagers::GetInstance()->GetShader("TextShader");
			std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, std::to_string(curLevel), Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1.2f);
			text->Set2DPosition(470.0f + j * 82.0f, 365.0f + i * 92.0f);
			m_listText.push_back(text);
		}
	}
	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "LEVEL", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f + 150.0f, (float)Globals::screenHeight / 2.0f - 210.0f));
	m_listText.push_back(text);
}

void Level::Draw()
{
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
}

void Level::Update(float deltaTime) 
{
	if (SaveData::GetInstance()->IsNewGame())
	{
		SaveData::GetInstance()->SaveLevel(0);
	}
	else
	{
		m_numPassedLevel = SaveData::GetInstance()->LoadLevel();
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void Level::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}