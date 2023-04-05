#include "Piece.h"
#include "ResourceManagers.h"

Piece::Piece(int row, int col, PieceType type):Sprite2D() {
	Init();
	m_row = row;
	m_col = col;
	m_type = type;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	SetModels(model);
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	SetShaders(shader);
	auto texture = ResourceManagers::GetInstance()->GetTexture("piece_hp.tga");
	switch (type) {
	case PieceType::HP:
		texture = ResourceManagers::GetInstance()->GetTexture("piece_hp.tga");
		break;
	case PieceType::Mana:
		texture = ResourceManagers::GetInstance()->GetTexture("piece_mana.tga");
		break;
	case PieceType::Poison:
		texture = ResourceManagers::GetInstance()->GetTexture("piece_poison.tga");
		break;
	case PieceType::Shield:
		texture = ResourceManagers::GetInstance()->GetTexture("piece_shield.tga");
		break;
	case PieceType::Spell:
		texture = ResourceManagers::GetInstance()->GetTexture("piece_spell.tga");
		break;
	case PieceType::Sword:
		texture = ResourceManagers::GetInstance()->GetTexture("piece_sword.tga");
		break;
	}
	SetTexture(texture);
	SetSize(Pi_size, Pi_size);
}
Piece::~Piece()
{
}

int Piece::GetCol()
{
	return m_col;
}

void Piece::SetCol(int x)
{
	m_col = x;
}

int Piece::GetRow()
{
	return m_row;
}

void Piece::SetRow(int y)
{
	m_row = y;
}

PieceType Piece::GetType() {
	return m_type;
}

//bool Piece::InRightPosition() {
//	if (this->Get2DPosition().x != 226 + m_col * 50) return false;
//	if (this->Get2DPosition().y != 226 + m_row * 50) return false;
//	return true;
//
//}
//std::string Piece::GetKind()
//{
//	return m_kind;
//}
//
//void Piece::SetKind(std::string kind)
//{
//	m_kind = kind;
//}