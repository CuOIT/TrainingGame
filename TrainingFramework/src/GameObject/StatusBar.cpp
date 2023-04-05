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
	m_hpBar->SetSize(180, 10);
;	texture = ResourceManagers::GetInstance()->GetTexture("mana_bar.tga");
	m_manaBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_manaBar->SetSize(180, 10);

	this->x = 20;

	if (isPlayer) {
		m_statusBarBG->Set2DPosition(180, 950);
		m_statusBarBG->SetSize(320, 80);
		m_hpBar->Set2DPosition(this->x+190, this->y+17);
		m_manaBar->Set2DPosition(this->x +190, this->y + 41);

	}
	else {
		m_statusBarBG->Set2DPosition(620, 950);
		m_statusBarBG->SetSize(-320, 80);
		m_hpBar->Set2DPosition(800-(this->x+190), this->y + 17);
		m_manaBar->Set2DPosition(800-(this->x + 190), this->y + 41);
	}
};
StatusBar::~StatusBar(){};


void StatusBar::SetHp(int hp) {
	m_hp = hp;
	m_hpBar->SetSize(180 * m_hp / m_maxHp, 10);
	if (m_isPlayer) {
	m_hpBar->Set2DPosition(this->x +100+ 90 * m_hp / m_maxHp, this->y + 17);
	}
	else {
		m_hpBar->Set2DPosition(800-(this->x + 100 + 90 * m_hp / m_maxHp), this->y + 17);
	}
}
void StatusBar::SetMana(int mana) {
	m_mana = mana;
	m_manaBar->SetSize(180 * m_mana / m_maxMana, 10);
	if (m_isPlayer) {
		m_manaBar->Set2DPosition(this->x + 100 + 90 * m_mana / m_maxMana, this->y + 41);
	}
	else {
		m_manaBar->Set2DPosition(800 - (this->x + 100 + 90 * m_mana / m_maxMana), this->y + 41);
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