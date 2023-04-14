#include "GSLevel.h"
#include "Camera.h"
#include "Player.h"
#include "Level.h"
#include "SaveData.h"
#include "PlayerManager.h"
#include"GSPlay.h"

GSLevel::GSLevel()
{
	m_isUpdateLevel = true;
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

	// button
	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_home.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50.0f, 50.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		SaveData::GetInstance()->SaveLevel(Level::GetInstance()->GetNumPassedLevel());
		SaveData::GetInstance()->SetIsNewGame(false);
		});
	m_listButton.push_back(button);

	// level
	m_level = Level::GetInstance();

	// player
	m_playerManager = PlayerManager::GetInstance();
}

void GSLevel::Exit()
{
}

void GSLevel::Pause()
{
}

void GSLevel::Resume()
{
	m_isUpdateLevel = true;
}

void GSLevel::HandleEvents()
{

}

void GSLevel::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSLevel::HandleTouchEvents(float x, float y, bool bIsPressed)
{
	m_playerManager->HandleTouchEvents(x, y, bIsPressed);
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
	m_playerManager->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (m_isUpdateLevel)
	{
		m_level->Update(deltaTime);
		std::cout << "Update level!" << "\n";
		m_isUpdateLevel = false;
	}
	if (m_level->GetSelectedLevel()) {
		std::shared_ptr enemy = SaveData::GetInstance()->LoadEnemy(m_level->GetSelectedLevel());
		GameStateMachine::GetInstance()->ChangeState(std::make_shared<GSPlay>(m_playerManager->GetPlayer(),enemy));
	}
}

void GSLevel::Draw()
{
	m_background->Draw();
	m_level->Draw();
	m_playerManager->Draw();
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