#include"WoodCharacter.h"
#include"Entity.h"
#include"GameButton.h"
#include"ResourceManagers.h"
#include"Font.h"
#include"Text.h"

WoodCharacter::WoodCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, std::string name, int maxHp, int maxMana, int attack, int defense) :
	Entity(model, shader, texture, numFrames, numActions, currentAction, frameTime, name, maxHp, maxMana, attack, defense) {

	//skill1
	m_skills[0]->SetTexture(ResourceManagers::GetInstance()->GetTexture("wood_skill1.tga"));
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
	std::vector<std::shared_ptr<Text>> detailOfSkill1;
	auto text = std::make_shared<Text>(shader, font, "Mana Cost: 50", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	text= std::make_shared<Text>(shader, font, "Increase armor by an amount equivalent to ", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f); 
	detailOfSkill1.push_back(text);
	text = std::make_shared<Text>(shader, font, "25 % of the maximum health of yourself", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill1);

	//skill2
	m_skills[1]->SetTexture(ResourceManagers::GetInstance()->GetTexture("wood_skill2.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill2;
	text = std::make_shared<Text>(shader, font, "Mana Cost: 100", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Summon a frog to attack the opponent with poisonous,", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "dealing poison damage equivalent to 10% of your maxHP.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Exist 3 turn.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill2);

	//skill3
	m_skills[2]->SetTexture(ResourceManagers::GetInstance()->GetTexture("wood_skill3.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill3;
	text = std::make_shared<Text>(shader, font, "Mana Cost: 150", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	text = std::make_shared<Text>(shader, font, "Destroy all shields in the board.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill3);

};
WoodCharacter::WoodCharacter() :Entity() {

};
WoodCharacter::~WoodCharacter() {

};
void WoodCharacter::UseSkill1() {
	SetDefense(GetDefense() + m_maxHp / 4);
}
void WoodCharacter::UseSkill2() {
	m_opponent->SetPoisoned(m_attack * 3);
}
void WoodCharacter::UseSkill3(std::shared_ptr<GameBoard> gameBoard) {
	gameBoard->SetDestroyList(gameBoard->GetPieceIndexType(3));
}
