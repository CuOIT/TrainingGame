#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include "Piece.h"
#include "GameField.h"
#include "Player.h"
#include"Entity.h"
#include <Windows.h>
#include "Level.h"
#include "SaveData.h"
#include "EndGameMenu.h"
#include "PlayerManager.h"

GSPlay::GSPlay()
{
	m_KeyPress = 0;
	
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_currentLevel = Level::GetInstance()->GetSelectedLevel();
	std::shared_ptr<Player> player = PlayerManager::GetInstance()->GetSelectedPlayer();
	std::shared_ptr<Entity> enemy = SaveData::GetInstance()->LoadEnemy();

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	std::cout << "Screen resolution: " << screenWidth << "x" << screenHeight << std::endl;
	std::cout << "current level: " << m_currentLevel << std::endl;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button 
	texture = ResourceManagers::GetInstance()->GetTexture("btn_more.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		this->Pause();
		});
	m_listButton.push_back(button);

	//animation
	std::string name = player->GetName();
	int maxHP = player->GetMaxHp();
	int maxMP = player->GetMaxMana();
	int attack = player->GetAttack();
	int defense = player->GetDefense();
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	player = std::make_shared<Player>(model, shader, texture, 6, 1, 0, 0.1f, name, maxHP, maxMP, attack, defense);
	player->SetTexture(ResourceManagers::GetInstance()->GetTexture(name + "_idle.tga"));
	player->Set2DPosition(GF_posXOfPlayer, GF_posYOfPlayer);
	player->SetSize(GF_playerWidth, GF_playerHeight);

	name = enemy->GetName();
	maxHP = enemy->GetMaxHp();
	maxMP = enemy->GetMaxMana();
	attack = enemy->GetAttack();
	defense = enemy->GetDefense();
	enemy = std::make_shared<Entity>(model, shader, texture, 6, 1, 0, 0.1f, name, maxHP, maxMP, attack, defense);
	enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture(name + "_idle.tga"));
	enemy->Set2DPosition(Globals::screenWidth - GF_posXOfPlayer, GF_posYOfPlayer);
	enemy->SetSize(-GF_playerWidth, GF_playerHeight);

	m_gameField = std::make_shared<GameField>(player, enemy);
	m_endGameMenu = std::make_shared<EndGameMenu>();

	m_KeyPress = 0;

	std::string soundName = "gsPlay_sound.wav";
	ResourceManagers::GetInstance()->PlaySound(soundName, true);

	std::cout << "GSPlay Init" << std::endl;

}

void GSPlay::Exit()

{
	std::cout << "Exit" << std::endl;
	std::string soundName = "gsPlay_sound.wav";
	ResourceManagers::GetInstance()->StopSound(soundName);
}


void GSPlay::Pause()
{
	std::cout << "Pause" << std::endl;
	m_isPause = true;
	m_pauseMenu = std::make_shared<PauseMenu>(this);
}
void GSPlay::Resume()
{
	std::cout << "Resume" << std::endl;
	m_isPause = false;
}


void GSPlay::HandleEvents()
{
	//Handle key event, insert more condition if you want to handle more than 4 default key
	if (m_KeyPress & 1)//Handle event when key 'A' was pressed
	{
		//Code to handle event
	}
	if (m_KeyPress & (1 << 1))//Handle event when key 'S' was pressed
	{
		//Code to handle event
	}
	if (m_KeyPress & (1 << 2))//Handle event when key 'D' was pressed
	{
		//Code to handle event
	}
	if (m_KeyPress & (1 << 3))//Handle event when key 'W' was pressed
	{
		//Code to handle event
	}
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)//Insert more case if you want to handle more than 4 default key
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT://Key 'A' was pressed
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWARD://Key 'S' was pressed
			m_KeyPress |= 1 << 1;
			break;
		case KEY_MOVE_RIGHT://Key 'D' was pressed
			m_KeyPress |= 1 << 2;
			break;
		case KEY_MOVE_FORWARD://Key 'W' was pressed
			m_KeyPress |= 1 << 3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT://Key 'A' was released
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWARD://Key 'S' was released
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;//Key 'D' was released
			break;
		case KEY_MOVE_FORWARD://Key 'W' was released
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

//Handle button event
void GSPlay::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	if (bIsPressed == false && m_isPause == false) {
		m_gameField->HandleClick(x, y);
		std::cout << "Handle Click" << std::endl;
	}

	if (m_isPause)
	{
		m_pauseMenu->HandleTouchEvents(x, y, bIsPressed);
	}

	if (Level::GetInstance()->GetIsEndGame())
	{
		m_endGameMenu->HandleTouchEvents(x, y, bIsPressed);
	}

	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(float x, float y)
{
	//Code to handle mouse event
	m_gameField->HandleMouseMoveEvents( x,  y);

}

void GSPlay::Update(float deltaTime)
{
	if (!m_isPause)
	{
		if (!Level::GetInstance()->GetIsEndGame())
		{
			m_gameField->Update(deltaTime);
			HandleEvents();
		}
		else
		{
			m_endGameMenu->Update(deltaTime);
		}
		//Update button list
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
	}
	else
	{
		m_pauseMenu->Update(deltaTime);
	}


	//Update animation list
	/*for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}*/
}

void GSPlay::Draw()
{
	//Render background
	m_background->Draw();
	m_gameField->Draw();

	if (m_isPause)
	{
		m_pauseMenu->Draw();
	}
	if (Level::GetInstance()->GetIsEndGame())
	{
		m_endGameMenu->Draw();
	}

	//Render button list
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//m_gameBoard->Draw();
	//Render animation list
	/*for (auto it : m_listAnimation)
	{
		it->Draw();
	}*/
}