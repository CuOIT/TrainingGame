#include"WoodCharacter.h"
#include"Entity.h"
#include"GameButton.h"
#include"ResourceManagers.h"
#include"Font.h"
#include"Text.h"

EarthCharacter::EarthCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, std::string name, int maxHp, int maxMana, int attack, int defense) :
	Entity(model, shader, texture, numFrames, numActions, currentAction, frameTime, name, maxHp, maxMana, attack, defense) {

	m_element = EARTH;
	//skill1
	m_skills[0]->SetTexture(ResourceManagers::GetInstance()->GetTexture("earth_skill1.tga"));
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
	std::vector<std::shared_ptr<Text>> detailOfSkill1;
	auto text = std::make_shared<Text>(shader, font, "POWER SHIELD", Vector4(0.95f, 0.f, 0.f, 1.0f), 0.7f);
	detailOfSkill1.push_back(text);
	text = std::make_shared<Text>(shader, font, "Mana Cost: 50", Vector4(0.f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	text= std::make_shared<Text>(shader, font, "Increase armor by an amount equivalent to ", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f); 
	detailOfSkill1.push_back(text);
	text = std::make_shared<Text>(shader, font, "25 % of the maximum health of yourself.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill1);

	//skill2
	m_skills[1]->SetTexture(ResourceManagers::GetInstance()->GetTexture("earth_skill2.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill2;
	text = std::make_shared<Text>(shader, font, "SPIRITS LAND", Vector4(0.95f, 0.f, 0.f, 1.0f), 0.7f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Mana Cost: 100", Vector4(0.f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Summon the spirits attack the opponent", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "dealing damage by 200% of your attack ", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "And make them cannot attack in 3 turns.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill2);

	//skill3
	m_skills[2]->SetTexture(ResourceManagers::GetInstance()->GetTexture("earth_skill3.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill3;
	text = std::make_shared<Text>(shader, font, "Mana Cost: 150", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	text = std::make_shared<Text>(shader, font, "Mana Cost: 150", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	text = std::make_shared<Text>(shader, font, "Destroy all shields in the board.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill3);

};
EarthCharacter::EarthCharacter() :Entity() {

};
EarthCharacter::~EarthCharacter() {

};
void EarthCharacter::UseSkill1() {
	SetDefense(GetDefense() + m_maxHp / 4);
}
void EarthCharacter::UseSkill2() {
	m_opponent->SetMuted(3);
	m_opponent->GetEffect()->SetNumFrames(16);
	m_opponent->GetEffect()->Set2DPosition(m_opponent->Get2DPosition().x, m_opponent->Get2DPosition().y + 30);
	m_opponent->GetEffect()->SetTexture(ResourceManagers::GetInstance()->GetTexture("earth_effect2.tga"), false);
	m_opponent->GetEffect()->SetLastTexture(nullptr);
	m_opponent->GetEffect()->SetSize(GF_playerWidth * 2 / 3, GF_playerHeight * 2/3);
	m_opponent->TakeDamage(2 * m_attack);
}
void EarthCharacter::UseSkill3(std::shared_ptr<GameBoard> gameBoard) {
	gameBoard->SetDestroyList(gameBoard->GetPieceIndexType(3));
}
