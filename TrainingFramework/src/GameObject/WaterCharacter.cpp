#include"WaterCharacter.h"
#include"GameBoard.h"
#include"GameButton.h"
#include"ResourceManagers.h"
WaterCharacter::WaterCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, std::string name, int maxHp, int maxMana, int attack, int defense) :
	Entity(model, shader, texture, numFrames, numActions, currentAction, frameTime, name, maxHp, maxMana, attack, defense) {
	m_element = WATER;

	//skill1
	m_skills[0]->SetTexture(ResourceManagers::GetInstance()->GetTexture("water_skill1.tga"));
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
	std::vector<std::shared_ptr<Text>> detailOfSkill1;
	auto text = std::make_shared<Text>(shader, font, "PURIFY", Vector4(0.99f, 0.f, 0.f, 1.0f), 0.7f);
	detailOfSkill1.push_back(text);
	 text = std::make_shared<Text>(shader, font, "Mana Cost: 50", Vector4(0.f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	text = std::make_shared<Text>(shader, font, "Remove all negative effects on the body ", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	//text = std::make_shared<Text>(shader, font, "25 % of the maximum health of yourself", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	//detailOfSkill1.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill1);

	//skill2
	m_skills[1]->SetTexture(ResourceManagers::GetInstance()->GetTexture("water_skill2.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill2;
	text = std::make_shared<Text>(shader, font, "ICY GRIP", Vector4(0.99f, 0.f, 0.f, 1.0f), 0.7f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Mana Cost: 100", Vector4(0.f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Freeze the opponent, causing them to lose two turns", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	//text = std::make_shared<Text>(shader, font, "dealing poison damage equivalent to 10% of your maxHP.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	//detailOfSkill2.push_back(text);
	//text = std::make_shared<Text>(shader, font, "Exist 3 turn.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	//detailOfSkill2.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill2);

	//skill3
	m_skills[2]->SetTexture(ResourceManagers::GetInstance()->GetTexture("water_skill3.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill3;
	text = std::make_shared<Text>(shader, font, "HEALING TOUCH", Vector4(0.95f, 0.f, 0.f, 1.0f), 0.7f);
	detailOfSkill3.push_back(text);
	text = std::make_shared<Text>(shader, font, "Mana Cost: 150", Vector4(0.f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	text = std::make_shared<Text>(shader, font, "Destroy all hearts in the board.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill3);

};
void WaterCharacter::UseSkill1() {
	SetBurned(0);
	SetFreezed(0);
	//SetPoisoned(false);
	SetMuted(0);
	SetPoisoned(0);
	GetEffect()->Set2DPosition(Get2DPosition().x, Get2DPosition().y+20);
	GetEffect()->SetTexture(ResourceManagers::GetInstance()->GetTexture("water_effect1.tga"), false);
	GetEffect()->SetLastTexture(nullptr);
	GetEffect()->SetSize(GF_playerWidth/2, GF_playerHeight/2);
	//std::cout << "Water1" << std::endl;

}
void WaterCharacter::UseSkill2() {
	m_opponent->SetFreezed(2);
	m_opponent->GetContinousEffect()->Set2DPosition(m_opponent->Get2DPosition().x, m_opponent->Get2DPosition().y);
	m_opponent->GetContinousEffect()->SetTexture(ResourceManagers::GetInstance()->GetTexture("water_effect22.tga"),false);
	m_opponent->GetContinousEffect()->SetLastTexture(ResourceManagers::GetInstance()->GetTexture("water_effect222.tga"));
	m_opponent->GetContinousEffect()->SetSize(GF_playerWidth, GF_playerHeight);
}
void WaterCharacter::UseSkill3(std::shared_ptr<GameBoard> gameBoard) {
	gameBoard->SetDestroyList(gameBoard->GetPieceIndexType(0));
}
