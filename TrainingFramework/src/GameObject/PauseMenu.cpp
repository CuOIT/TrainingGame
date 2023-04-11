#include "PauseMenu.h"
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "GameStates/GSPlay.h"

PauseMenu::PauseMenu(GSPlay *gs) : Sprite2D()
{
	this->SetSize(200, 200);
	Init(gs);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init(GSPlay *gs)
{
	// bg pause
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");
	m_bgPause = std::make_shared<Sprite2D>(model, shader, texture);
	m_bgPause->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f);
	m_bgPause->SetSize(400.0f, 200.0f);

	// pause header
	texture = ResourceManagers::GetInstance()->GetTexture("header.tga");
	m_pauseHeader = std::make_shared<Sprite2D>(model, shader, texture);
	m_pauseHeader->Set2DPosition((float)Globals::screenWidth / 2.0f, (float)Globals::screenHeight / 2.0f - 70.0f);
	m_pauseHeader->SetSize(250.0f, 75.0f);

	// btn
	// sound on
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sound_on.tga");
	m_btnSoundOn = std::make_shared<GameButton>(model, shader, texture);
	m_btnSoundOn->Set2DPosition((float)Globals::screenWidth / 2.0f - 120.0f, (float)Globals::screenHeight / 2.0f + 25.0f);
	m_btnSoundOn->SetOnClick([this]() {
		ResourceManagers::GetInstance()->StopSound("gsPlay_sound.wav");
		m_isPlaySound = false;
		});
	// sound off
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sound_off.tga");
	m_btnSoundOff = std::make_shared<GameButton>(model, shader, texture);
	m_btnSoundOff->Set2DPosition((float)Globals::screenWidth / 2.0f - 120.0f, (float)Globals::screenHeight / 2.0f + 25.0f);
	m_btnSoundOff->SetOnClick([this]() {
		ResourceManagers::GetInstance()->PlaySound("gsPlay_sound.wav");
		m_isPlaySound = true;
		});
	// home
	texture = ResourceManagers::GetInstance()->GetTexture("btn_back.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f - 45.0f, (float)Globals::screenHeight / 2.0f + 25.0f);
	button->SetSize(60.0f, 60.0f);
;	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
	// restart
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f + 30.0f, (float)Globals::screenHeight / 2.0f + 25.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);
	// resume
	texture = ResourceManagers::GetInstance()->GetTexture("btn_resume.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2.0f + 105.0f, (float)Globals::screenHeight / 2.0f + 25.0f);
	button->SetSize(60.0f, 60.0f);
	button->SetOnClick([this, gs]() {
		PauseMenu::SetSize(0, 0);
		gs->SetIsPause(false);
		});
	m_listButton.push_back(button);

	// txt pause
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Woodlook-nvyP.ttf");
	std::shared_ptr<Text> text = std::make_shared<Text>(shader, font, "PAUSE", Vector4(50.0f, 30.0f, 0.0f, 1.0f), 1.2f);
	text->Set2DPosition(Vector2((float)Globals::screenWidth / 2.0f - 50.0f, (float)Globals::screenHeight / 2.0f - 60.0f));
	m_listText.push_back(text);
}

void PauseMenu::Update(float deltaTime)
{
	if (m_isPlaySound)
	{
		m_btnSoundOn->SetSize(60.0f, 60.0f);
		m_btnSoundOff->SetSize(0, 0);
	}
	else
	{
		m_btnSoundOff->SetSize(60.0f, 60.0f);
		m_btnSoundOn->SetSize(0, 0);
	}
}

void PauseMenu::Draw()
{
	m_bgPause->Draw();
	m_pauseHeader->Draw();
	m_btnSoundOn->Draw();
	m_btnSoundOff->Draw();

	for (auto it : m_listText)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

void PauseMenu::HandleTouchEvents(int x, int y, bool isPressed)
{
	m_btnSoundOn->HandleTouchEvents(x, y, isPressed);
	m_btnSoundOff->HandleTouchEvents(x, y, isPressed);
	for (auto it : m_listButton)
	{
		it->HandleTouchEvents(x, y, isPressed);
	}
}