#include"WoodCharacter.h"
#include"Entity.h"
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
