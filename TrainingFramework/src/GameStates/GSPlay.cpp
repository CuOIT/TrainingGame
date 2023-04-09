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

GSPlay::GSPlay()
{
	m_KeyPress = 0;
	m_currentLevel = Level::GetInstance()->GetSelectedLevel();

}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	std::cout << "Pi :" << PI << std::endl;
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
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("warrior1_idle.tga");
	std::shared_ptr<Player> player = std::make_shared<Player>(model, shader, texture, 6, 1, 0, 0.1f, "warrior1", 200, 200, 10, 0);
	player->Set2DPosition(GF_posXOfPlayer, GF_posYOfPlayer);
	player->SetSize(GF_playerWidth, GF_playerHeight);
	texture = ResourceManagers::GetInstance()->GetTexture("warrior1_idle.tga");
	std::shared_ptr<Entity> enermy = std::make_shared<Entity>(model, shader, texture, 6, 1, 0, 0.1f, "warrior2", 200, 200, 10, 0);
	enermy->Set2DPosition(Globals::screenWidth - GF_posXOfPlayer, GF_posYOfPlayer);
	enermy->SetSize(-GF_playerWidth, GF_playerHeight);
	m_gameField = std::make_shared<GameField>(player, enermy);

	m_KeyPress = 0;

	std::string name = "gsPlay_sound.wav";
	ResourceManagers::GetInstance()->PlaySound(name, true);

	std::cout << "GSPlay Init" << std::endl;

}

void GSPlay::Exit()

{
	std::cout << "Exit" << std::endl;
	std::string name = "gsPlay_sound.wav";
	ResourceManagers::GetInstance()->StopSound(name);
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

}

void GSPlay::Update(float deltaTime)
{
	if (!m_isPause)
	{
		m_gameField->Update(deltaTime);
		HandleEvents();

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