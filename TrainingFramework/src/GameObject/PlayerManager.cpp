#include "PlayerManager.h"
#include "ResourceManagers.h"
#include "SaveData.h"
#include "GameStates/GameStateMachine.h"
#include "Player.h"

PlayerManager::PlayerManager()
{
	Init();
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Init()
{
	if (SaveData::GetInstance()->GetIsNewGame())
	{
		std::string fileName = "Player.txt";
		SaveData::GetInstance()->Init(fileName);
	}
	std::shared_ptr<Player> player = SaveData::GetInstance()->LoadPlayer();
	std::string name = player->GetName();
	int maxHP = player->GetMaxHp();
	int maxMP = player->GetMaxMana();
	int attack = player->GetAttack();
	int defense = player->GetDefense();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	// bg for menu
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.0f - 150.0f, Globals::screenHeight / 2.0f);
	sprite->SetSize(Globals::screenWidth / 2.0 - 40, Globals::screenHeight / 2);
	m_listSprite2D.push_back(sprite);

	// header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 4, Globals::screenHeight / 2.0f - 180.0f);
	sprite->SetSize(220.0f, 70.0f);
	m_listSprite2D.push_back(sprite);

	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "PLAYER", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 215.0f, (float)Globals::screenHeight / 2.0f - 172.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, name, Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 200.0f, Globals::screenHeight / 2.0f - 100.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "HP: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 250.0f, Globals::screenHeight / 2.0f + 100.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, std::to_string(maxHP), Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 180.0f, Globals::screenHeight / 2.0f + 100.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, "MP: ", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 250.0f, Globals::screenHeight / 2.0f + 130.0f));
	m_listText.push_back(text);

	text = std::make_shared<Text>(shader, font, std::to_string(maxMP), Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth / 2.0f - 180.0f, Globals::screenHeight / 2.0f + 130.0f));
	m_listText.push_back(text);
	
	// animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	player = std::make_shared<Player>(model, shader, texture, 6, 1, 0, 0.1f, name, maxHP, maxMP, attack, defense);
	player->SetTexture(ResourceManagers::GetInstance()->GetTexture(name + "_idle.tga"));
	player->Set2DPosition(Globals::screenWidth / 2.0f - 150.0f, Globals::screenHeight / 2.0f - 50.0f);
	player->SetSize(200, 200);
	m_listAnimation.push_back(player);
}

void PlayerManager::Draw()
{
	for (auto it : m_listSprite2D)
	{
		it->Draw();
	}
	for (auto it : m_listAnimation)
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

void PlayerManager::Update(float deltaTime)
{
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void PlayerManager::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}