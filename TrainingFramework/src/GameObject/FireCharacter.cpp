#include"FireCharacter.h"
#include"Entity.h"
#include"ResourceManagers.h"
#include"GameButton.h"
FireCharacter::FireCharacter():Entity() {

};

FireCharacter::FireCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, std::string name, int maxHp, int maxMana, int attack, int defense) :
	Entity(model, shader, texture, numFrames, numActions, currentAction, frameTime, name, maxHp, maxMana, attack, defense) {
	m_skills[0]->SetTexture(ResourceManagers::GetInstance()->GetTexture("fire_skill1.tga"));
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
	std::vector<std::shared_ptr<Text>> detailOfSkill1;
	auto text = std::make_shared<Text>(shader, font, "Mana Cost: 50", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	text = std::make_shared<Text>(shader, font, "Double attack this turn ", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	//text = std::make_shared<Text>(shader, font, "25 % of the maximum health of yourself", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	//detailOfSkill1.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill1);

	//skill2
	m_skills[1]->SetTexture(ResourceManagers::GetInstance()->GetTexture("fire_skill2.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill2;
	text = std::make_shared<Text>(shader, font, "Mana Cost: 100", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Summon holy flames, burning 5% of maxHP & 5% of maxMana", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, " of the opponent each turn.Exist 3 turn", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	//text = std::make_shared<Text>(shader, font, "Exist 3 turn.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	//detailOfSkill2.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill2);

	//skill3
	m_skills[2]->SetTexture(ResourceManagers::GetInstance()->GetTexture("fire_skill3.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill3;
	text = std::make_shared<Text>(shader, font, "Mana Cost: 150", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	text = std::make_shared<Text>(shader, font, "Destroy all swords in the board.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill3);

};
FireCharacter::~FireCharacter(){

};
void FireCharacter::UseSkill1() {
	m_opponent->SetBurned(true);
}
void FireCharacter::UseSkill2() {
	m_opponent->SetHp(m_opponent->GetCurrentHp() - 5 * m_attack);
}
void FireCharacter::UseSkill3(std::shared_ptr<GameBoard> gameBoard) {
	gameBoard->SetDestroyList(gameBoard->GetPieceIndexType(5));
}
