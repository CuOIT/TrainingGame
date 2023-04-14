#include"FireCharacter.h"
#include"Entity.h"
FireCharacter::FireCharacter():Entity() {

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
