#include"FireCharacter.h"
#include"Entity.h"
#include"ResourceManagers.h"
#include"GameButton.h"
FireCharacter::FireCharacter():Entity() {

};

FireCharacter::FireCharacter(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, std::string name, int maxHp, int maxMana, int attack, int defense) :
	Entity(model, shader, texture, numFrames, numActions, currentAction, frameTime, name, maxHp, maxMana, attack, defense) {

	m_element = FIRE;
	m_power = false;
	m_skills[0]->SetTexture(ResourceManagers::GetInstance()->GetTexture("fire_skill1.tga"));
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto font = ResourceManagers::GetInstance()->GetFont("Alkatra-VariableFont_wght.ttf");
	std::vector<std::shared_ptr<Text>> detailOfSkill1;
	auto text = std::make_shared<Text>(shader, font, "FLAME BOOST", Vector4(0.95f, 0.f, 0.f, 1.0f), 0.7f);
	detailOfSkill1.push_back(text);
	text = std::make_shared<Text>(shader, font, "Mana Cost: 50", Vector4(0.f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);
	text = std::make_shared<Text>(shader, font, "Double attack power this turn ", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill1.push_back(text);

	m_detailOfSKills.push_back(detailOfSkill1);

	//skill2
	m_skills[1]->SetTexture(ResourceManagers::GetInstance()->GetTexture("fire_skill2.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill2;
	text = std::make_shared<Text>(shader, font, "HOLY FLAME", Vector4(0.95f, 0.f, 0.f, 1.0f), 0.7f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Mana Cost: 100", Vector4(0.f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, "Summon holy flames, burning 5% of maxHP & 5% of maxMana", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	text = std::make_shared<Text>(shader, font, " of the opponent each turn.Exist 3 turns.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill2.push_back(text);
	//text = std::make_shared<Text>(shader, font, "Exist 3 turn.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	//detailOfSkill2.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill2);

	//skill3
	m_skills[2]->SetTexture(ResourceManagers::GetInstance()->GetTexture("fire_skill3.tga"));
	std::vector<std::shared_ptr<Text>> detailOfSkill3;
	text = std::make_shared<Text>(shader, font, "INFERNO BLAST", Vector4(0.95f, 0.f, 0.f, 1.0f), 0.7f);
	detailOfSkill3.push_back(text);
	text = std::make_shared<Text>(shader, font, "Mana Cost: 150", Vector4(0.f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	text = std::make_shared<Text>(shader, font, "Destroy all swords in the board.", Vector4(0.95f, 0.98f, 0.98f, 1.0f), 0.5f);
	detailOfSkill3.push_back(text);
	m_detailOfSKills.push_back(detailOfSkill3);

};
FireCharacter::~FireCharacter(){

};
void FireCharacter::UseSkill1() {
	m_power = true;
	GetEffect()->Set2DPosition(Get2DPosition().x,Get2DPosition().y + 20);
	GetEffect()->SetTexture(ResourceManagers::GetInstance()->GetTexture("fire_effect11.tga"), false);
	GetEffect()->SetLastTexture(nullptr);
	GetEffect()->SetSize(GF_playerWidth/2, GF_playerHeight/2);
}
void FireCharacter::UseSkill2() {
	m_opponent->SetBurned(3);
	m_opponent->GetEffect()->Set2DPosition(m_opponent->Get2DPosition().x, m_opponent->Get2DPosition().y + 20);
	m_opponent->GetEffect()->SetTexture(ResourceManagers::GetInstance()->GetTexture("fire_effect2.tga"), false);
	m_opponent->GetEffect()->SetLastTexture(nullptr);
	m_opponent->GetEffect()->SetSize(GF_playerWidth, GF_playerHeight);
	int def = m_opponent->GetDefense();
	m_opponent->TakeDamage(m_attack * 2+def);
	m_opponent->SetDefense(def);
}
void FireCharacter::UseSkill3(std::shared_ptr<GameBoard> gameBoard) {
	gameBoard->SetDestroyList(gameBoard->GetPieceIndexType(5));
}

void FireCharacter::Attack(float deltaTime) {
	if (m_power) {
		m_attack *= 2;
	}
	Entity::Attack(deltaTime);
	if (m_attackNum == 0) {
		m_power = false;
	}
}