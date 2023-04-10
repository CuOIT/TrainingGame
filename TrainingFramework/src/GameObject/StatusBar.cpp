#include"Sprite2D.h"
#include"Entity.h"
#include"StatusBar.h"
#include"Font.h"
#include"ResourceManagers.h"
StatusBar::StatusBar(int maxHp, int maxMana, bool isPlayer) :m_maxHp(maxHp), m_maxMana(maxMana), m_hp(maxHp), m_mana(0), m_shield(0), m_poison(0), m_isPlayer(isPlayer) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("status_bar.tga");
	m_statusBarBG = std::make_shared<Sprite2D>(model, shader, texture);
	texture = ResourceManagers::GetInstance()->GetTexture("hp_bar.tga");
	m_hpBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_hpBar->SetSize(SB_maxBarWidth, SB_barHeight);
	;	texture = ResourceManagers::GetInstance()->GetTexture("mana_bar.tga");
	m_manaBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_manaBar->SetSize(0,0);
	texture = ResourceManagers::GetInstance()->GetTexture("piece_shield.tga");
	m_shieldStt = std::make_shared<Sprite2D>(model, shader, texture);
	m_shieldStt->SetSize(SB_effectSize, SB_effectSize);
	texture = ResourceManagers::GetInstance()->GetTexture("poisonStt.tga");
	m_poisonStt = std::make_shared<Sprite2D>(model, shader, texture);
	m_poisonStt->SetSize(SB_effectSize, SB_effectSize);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
	m_shieldText = std::make_shared<Text>(shader, font, "", Vector4(0.95f, 0.98f,0.98f, 1.0f), 0.5f);
	m_poisonText = std::make_shared<Text>(shader, font, "", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);



	if (isPlayer) {
		m_statusBarBG->Set2DPosition(SB_posX + SB_width / 2, SB_posY + SB_height / 2);
		m_statusBarBG->SetSize(SB_width, SB_height);
		m_hpBar->Set2DPosition(SB_posXOfBar + SB_maxBarWidth / 2, SB_posYOfHpBar + SB_barHeight / 2);
		m_manaBar->Set2DPosition(SB_posXOfBar + SB_maxBarWidth / 2, SB_posYOfManaBar + SB_barHeight / 2);
		m_shieldStt->Set2DPosition(SB_posX + SB_width / 3, SB_posY + 7*SB_height/10 + SB_effectSize/2);
		m_poisonStt->Set2DPosition(SB_posX + SB_width / 3 + SB_effectSize+2, SB_posY +7* SB_height/10 + SB_effectSize/2);

		/*m_shieldText->Set2DPosition(SB_posX + SB_width / 3 + SB_effectSize/2, SB_posY + 7 * SB_height / 10 + SB_effectSize);
		m_poisonText->Set2DPosition(SB_posX + SB_width / 3 +SB_effectSize + SB_effectSize/2, SB_posY + 7 * SB_height / 10 +SB_effectSize);*/

	}
	else {
		m_statusBarBG->Set2DPosition(Globals::screenWidth - (SB_posX + SB_width / 2), SB_posY + SB_height / 2);
		m_statusBarBG->SetSize(-SB_width, SB_height);
		m_hpBar->Set2DPosition(Globals::screenWidth - (SB_posXOfBar + SB_maxBarWidth / 2), SB_posYOfHpBar + SB_barHeight / 2);
		m_manaBar->Set2DPosition(Globals::screenWidth - (SB_posXOfBar + SB_maxBarWidth / 2), SB_posYOfManaBar + SB_barHeight / 2);
		m_shieldStt->Set2DPosition(Globals::screenWidth - (SB_posX + SB_width / 3), SB_posY + 7 * SB_height / 10 + SB_effectSize / 2);
		m_poisonStt->Set2DPosition(Globals::screenWidth - (SB_posX + SB_width / 3+SB_effectSize), SB_posY + 7 * SB_height / 10 + SB_effectSize / 2);

		/*m_shieldText->Set2DPosition(Globals::screenWidth - (SB_posX + SB_width / 3 + SB_effectSize/2), SB_posY + 7 * SB_height / 10 +SB_effectSize);
		m_poisonText->Set2DPosition(Globals::screenWidth - (SB_posX + SB_width / 3 + +SB_effectSize + SB_effectSize/2), SB_posY + 7 * SB_height / 10 +  SB_effectSize);*/
	}
		m_shieldText->Set2DPosition(m_shieldStt->Get2DPosition().x+3, m_shieldStt->Get2DPosition().y+10);
		m_poisonText->Set2DPosition(m_poisonStt->Get2DPosition().x+3,m_poisonStt->Get2DPosition().y+10);
};
StatusBar::~StatusBar() {};


void StatusBar::SetHp(int hp) {
	if (abs(hp - m_hp) <= 1) m_hp = hp;
	else if (hp > m_hp) m_hp += 2;
	else m_hp -= 2;
	m_hpBar->SetSize(SB_maxBarWidth * m_hp / m_maxHp, SB_barHeight);
	if (m_isPlayer) {
		m_hpBar->Set2DPosition(SB_posXOfBar + SB_maxBarWidth * m_hp / m_maxHp / 2, SB_posYOfHpBar + SB_barHeight / 2);
	}
	else {
		m_hpBar->Set2DPosition(Globals::screenWidth - (SB_posXOfBar + SB_maxBarWidth * m_hp / m_maxHp / 2), SB_posYOfHpBar + SB_barHeight / 2);
	}
}
void StatusBar::SetMana(int mana) {
	if (abs(mana - m_mana) <= 1) m_mana = mana;
	else if (mana > m_mana) m_mana += 2;
	else m_mana -= 2;
	m_manaBar->SetSize(SB_maxBarWidth * m_mana / m_maxMana, SB_barHeight);
	if (m_isPlayer) {
		m_manaBar->Set2DPosition(SB_posXOfBar + SB_maxBarWidth * m_mana / m_maxMana / 2, SB_posYOfManaBar + SB_barHeight / 2);
	}
	else {
		m_manaBar->Set2DPosition(Globals::screenWidth - (SB_posXOfBar + SB_maxBarWidth * m_mana / m_maxMana / 2), SB_posYOfManaBar + SB_barHeight / 2);
	}
}
void StatusBar::SetShiled(int shield) {
	if (abs(shield - m_shield) <= 1) m_shield = shield;
	else if (shield > m_shield) m_shield += 1;
	else m_shield-=1;
	m_shieldText->SetText(std::to_string(m_shield));
}
void StatusBar::SetPoison(int poison) {
	m_poison = poison;
	m_poisonText->SetText(std::to_string(m_poison));

}
void StatusBar::Update(float deltaTime, std::shared_ptr<Entity> entity) {
	if (entity->IsAlive()) {

		if (m_hp > entity->GetCurrentHp()) {
			entity->SetTexture(ResourceManagers::GetInstance()->GetTexture("warrior1_hurt.tga"));
		}
		else if(entity->GetAttackNum()==0)
		{
			entity->SetTexture(ResourceManagers::GetInstance()->GetTexture("warrior1_idle.tga"));
		}
	}
	this->SetHp(entity->GetCurrentHp());
	this->SetMana(entity->GetCurrentMana());
	this->SetShiled(entity->GetDefense());
	this->SetPoison(entity->GetPoison());
}
void StatusBar::Draw() {
	m_statusBarBG->Draw();
	m_hpBar->Draw();
	m_manaBar->Draw();
	if (m_shield > 0) {
		m_shieldStt->Draw();
		m_shieldText->Draw();
	}
	if (m_poison > 0) {
		m_poisonStt->Draw();
		m_poisonText->Draw();
	}
}