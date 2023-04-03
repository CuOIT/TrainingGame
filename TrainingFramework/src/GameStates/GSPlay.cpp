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


GSPlay::GSPlay()
{
	m_KeyPress = 0;
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("HP_bar.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	/*m_background->Set2DPosition(620, 950);
	m_background->SetSize(-320, 80);*/
	m_background->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);

	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0f, 50.0f);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0f);
	m_score->Set2DPosition(Vector2(5.0f, 25.0f));

	//animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("warrior3_auto_x24.tga");
	//for (int i = 0; i < 1; i++) {
		std::shared_ptr<Player> player = std::make_shared<Player>(model,shader,texture,8,6,5,0.05f,"Player",200,200,2,0);
		player->Set2DPosition(100, 700);
		player->SetSize(250, 250);
		std::shared_ptr<Entity> enermy = std::make_shared<Entity>(model, shader, texture, 8, 6, 4, 0.05f, "Player", 200, 200, 2, 0);
		enermy->Set2DPosition(600, 700);
		enermy->SetSize(-250, 250);
		m_gameField = std::make_shared<GameField>(player, enermy);

		//std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture,8, 6,5	,1.f);
		//obj->Set2DPosition(100, 700);
		//obj->SetSize(250,250);
		//m_listAnimation.push_back(obj);
	//}
	m_KeyPress = 0;

	std::string name = "gsPlay_sound.wav";
	//ResourceManagers::GetInstance()->PlaySound(name, true);
	std::cout << "GSPlay Init" << std::endl;
	
}

void GSPlay::Exit()

{
	std::string name = "gsPlay_sound.wav";
	ResourceManagers::GetInstance()->StopSound(name);
}


void GSPlay::Pause()
{
	std::string name = "gsPlay_sound.wav";
	ResourceManagers::GetInstance()->StopSound(name);
}

void GSPlay::Resume()
{
	std::string name = "gsPlay_sound.wav";
	ResourceManagers::GetInstance()->PlaySound(name, true);
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
			m_KeyPress |= 1<<1;
			break;
		case KEY_MOVE_RIGHT://Key 'D' was pressed
			m_KeyPress |= 1<<2;
			break;
		case KEY_MOVE_FORWARD://Key 'W' was pressed
			m_KeyPress |= 1<<3;
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
	if (bIsPressed == false) {
	m_gameField->HandleClick(x, y);
	std::cout << "Handle Click" << std::endl;
	}

	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
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
	m_gameField->Update(deltaTime);
	HandleEvents();

	//Update button list
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	//Update animation list
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	//Render background
	m_background->Draw();
	//Render score text
	m_score->Draw();
	m_gameField->Draw();

	//Render button list
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//m_gameBoard->Draw();
	//Render animation list
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}