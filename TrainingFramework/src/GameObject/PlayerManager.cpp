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
	m_listPlayer = SaveData::GetInstance()->LoadPlayer();
	m_selectedPlayer = m_listPlayer.front();
	std::string name = m_selectedPlayer->GetName();
	int maxHP = m_selectedPlayer->GetMaxHp();
	int maxMP = m_selectedPlayer->GetMaxMana();
	int attack = m_selectedPlayer->GetAttack();
	int defense = m_selectedPlayer->GetDefense();

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

	// btn
	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 280.0f, Globals::screenHeight / 2.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		m_listPlayer.insert(m_listPlayer.begin(), m_listPlayer.back());
		m_listPlayer.pop_back();
		m_selectedPlayer = m_listPlayer.front();
		m_isSwitchPlayer = true;
		});
	m_listButton.push_back(button);

	// next
	texture = ResourceManagers::GetInstance()->GetTexture("btn_resume.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.0f - 20.0f, Globals::screenHeight / 2.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		m_listPlayer.push_back(m_selectedPlayer);
		m_listPlayer.erase(m_listPlayer.begin());
		m_selectedPlayer = m_listPlayer.front();
		m_isSwitchPlayer = true;
		});
	m_listButton.push_back(button);

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
	m_selectedPlayer = std::make_shared<Player>(model, shader, texture, 6, 1, 0, 0.1f, name, maxHP, maxMP, attack, defense);
	m_selectedPlayer->SetTexture(ResourceManagers::GetInstance()->GetTexture(name + "_idle.tga"));
	m_selectedPlayer->Set2DPosition(Globals::screenWidth / 2.0f - 150.0f, Globals::screenHeight / 2.0f - 40.0f);
	m_selectedPlayer->SetSize(200, 200);
	m_listAnimation.push_back(m_selectedPlayer);
}

void PlayerManager::Draw()
{
	//m_selectedPlayer->Draw();
	
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
	m_selectedPlayer->Update(deltaTime);
	if (m_isSwitchPlayer)
	{
		m_listText[1]->SetText(m_selectedPlayer->GetName());
		m_listText[3]->SetText(std::to_string(m_selectedPlayer->GetMaxHp()));
		m_listText[5]->SetText(std::to_string(m_selectedPlayer->GetMaxMana()));
		m_listAnimation[0]->SetTexture(ResourceManagers::GetInstance()->GetTexture(m_selectedPlayer->GetName() + "_idle.tga"));
		m_isSwitchPlayer = false;
	}

	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	/*for (auto it : m_listText)
	{
		it->Update(deltaTime);
	}*/
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