#include"WaterCharacter.h"
#include"GameBoard.h"
void WaterCharacter::UseSkill1() {
	SetBurned(false);
	SetFreezed(false);
	SetPoisoned(false);
}
void WaterCharacter::UseSkill2() {
	m_opponent->SetFreezed(true);
}
void WaterCharacter::UseSkill3(std::shared_ptr<GameBoard> gameBoard) {
	gameBoard->SetDestroyList(gameBoard->GetPieceIndexType(0));
}
