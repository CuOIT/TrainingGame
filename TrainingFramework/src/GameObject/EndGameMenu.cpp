#include "EndGameMenu.h"
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "GameStates/GSPlay.h"
#include "Level.h"

EndGameMenu::EndGameMenu(bool won) : Sprite2D()
{
	m_isWon = won;
	Init();
}

EndGameMenu::~EndGameMenu()
{
}

void EndGameMenu::Init()
{
	// bg
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	m_bgMenu = std::make_shared<Sprite2D>(model, shader, texture);
	m_bgMenu->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_bgMenu->SetSize(400.0f, 200.0f);

	// header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	m_header = std::make_shared<Sprite2D>(model, shader, texture);
	m_header->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f - 70.0f);
	m_header->SetSize(250.0f, 75.0f);

	// btn
	// back
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f - 100.0f, (float)Globals::screenHeight / 2.0f + 25.0f);
	button->SetSize(60.0f, 60.0f);
	;	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
	// restart
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f + 25.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		std::shared_ptr<GSPlay> state = std::dynamic_pointer_cast<GSPlay>(GameStateMachine::GetInstance()->CurrentState());
		//auto nextState = std::make_shared<GSPlay>(*state);
		auto player = state->GetPlayer();
		int currentLevel = state->GetCurrentLevel();
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(std::make_shared<GSPlay>(player, currentLevel));
		});
	m_listButton.push_back(button);
	// next level
	if (m_isWon) {

		texture = ResourceManagers::GetInstance()->GetTexture("btn_resume.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition((float)Globals::screenWidth / 2.0f + 105.0f, (float)Globals::screenHeight / 2.0f + 25.0f);
		button->SetSize(60.0f, 60.0f);
		button->SetOnClick([this]() {
			//EndGameMenu::SetSize(0, 0);
			std::shared_ptr<GSPlay> state= std::dynamic_pointer_cast<GSPlay>(GameStateMachine::GetInstance()->CurrentState());
			//auto nextState = std::make_shared<GSPlay>(*state);
			auto player = state->GetPlayer();
			int currentLevel = state->GetCurrentLevel();
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->ChangeState(std::make_shared<GSPlay>(player,currentLevel+1));
			/*GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
			Level::GetInstance()->SetIsEndGame(false);
			Level::GetInstance()->SetSelectedLevel(Level::GetInstance()->GetSelectedLevel() + 1);*/
			});
		m_listButton.push_back(button);
	}

	// txt win
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 40.0f, (float)Globals::screenHeight / 2.0f - 60.0f));
	if (m_isWon) {
		text->SetText("WIN");
	}
	else text->SetText("Game Over");
	m_listText.push_back(text);
}

void EndGameMenu::Draw()
{
	m_bgMenu->Draw();
	m_header->Draw();

	for (auto it : m_listText)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

void EndGameMenu::HandleTouchEvents(int x, int y, bool isPressed)
{
	for (auto it : m_listButton)
	{
		it->HandleTouchEvents(x, y, isPressed);
	}
}