#include"Sprite2D.h"
#include"Entity.h"
#include"StatusBar.h"
#include"ResourceManagers.h"
StatusBar::StatusBar(int maxHp, int maxMana, bool isPlayer) :m_maxHp(maxHp), m_maxMana(maxMana), m_hp(maxHp), m_mana(maxMana),m_isPlayer(isPlayer) {
	this->y = 910;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("status_bar.tga");
	m_statusBarBG	= std::make_shared<Sprite2D>(model, shader, texture);
	texture = ResourceManagers::GetInstance()->GetTexture("hp_bar.tga");
	m_hpBar			= std::make_shared<Sprite2D>(model, shader, texture);
	m_hpBar->SetSize(SB_maxBarWidth, SB_barHeight);
;	texture = ResourceManagers::GetInstance()->GetTexture("mana_bar.tga");
	m_manaBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_manaBar->SetSize(SB_maxBarWidth, SB_barHeight);

	this->x = 20;

	if (isPlayer) {
		m_statusBarBG->Set2DPosition(SB_posX+SB_width/2, SB_posY+SB_height/2);
		m_statusBarBG->SetSize(SB_width, SB_height);
		m_hpBar->Set2DPosition(SB_posXOfBar + SB_maxBarWidth/2, SB_posYOfHpBar+SB_barHeight/2);
		m_manaBar->Set2DPosition(SB_posXOfBar + SB_maxBarWidth / 2, SB_posYOfHpBar + SB_barHeight / 2);

	}
	else {
		m_statusBarBG->Set2DPosition(Globals::screenWidth-(SB_posX+SB_width/2), SB_posY + SB_height / 2);
		m_statusBarBG->SetSize(-SB_width, SB_height);
		m_hpBar->Set2DPosition(Globals::screenWidth-(SB_posXOfBar + SB_maxBarWidth / 2), SB_posYOfHpBar + SB_barHeight / 2);
		m_manaBar->Set2DPosition(Globals::screenWidth - (SB_posXOfBar + SB_maxBarWidth / 2), SB_posYOfManaBar + SB_barHeight / 2);
	}
};
StatusBar::~StatusBar(){};


void StatusBar::SetHp(int hp) {
	m_hp = hp;
	m_hpBar->SetSize(SB_maxBarWidth * m_hp / m_maxHp, SB_barHeight);
	if (m_isPlayer) {
	m_hpBar->Set2DPosition(SB_posXOfBar+ SB_maxBarWidth * m_hp / m_maxHp / 2, SB_posYOfHpBar + SB_barHeight / 2);
	}
	else {
		m_hpBar->Set2DPosition(Globals::screenWidth - (SB_posXOfBar + SB_maxBarWidth * m_hp / m_maxHp / 2), SB_posYOfHpBar + SB_barHeight / 2);
	}
}
void StatusBar::SetMana(int mana) {
	m_mana = mana;
	m_manaBar->SetSize(SB_maxBarWidth * m_mana / m_maxMana, SB_barHeight);
	if (m_isPlayer) {
		m_manaBar->Set2DPosition(SB_posXOfBar + SB_maxBarWidth * m_mana / m_maxMana / 2, SB_posYOfManaBar + SB_barHeight / 2);
	}
	else {
		m_manaBar->Set2DPosition(Globals::screenWidth - (SB_posXOfBar + SB_maxBarWidth * m_mana / m_maxMana / 2), SB_posYOfManaBar + SB_barHeight / 2);
	}
}
void StatusBar::Update(float deltaTime,std::shared_ptr<Entity> entity) {
	this->SetHp(entity->GetCurrentHp());
	this->SetMana(entity->GetCurrentMana());

}
void StatusBar::Draw() {
	m_statusBarBG->Draw();
	m_hpBar->Draw();
	m_manaBar->Draw();

}