#include "Piece.h"
#include "ResourceManagers.h"

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

void Piece::Dropping(float s) {
	if (abs(this->Get2DPosition().y - 226 - 50 * m_row) >= s) {
		this->Set2DPosition(this->Get2DPosition().x,this->Get2DPosition().y+int(s));
	}
	else {
		this->Set2DPosition(this->Get2DPosition().x, 226 + 50 * m_row);
	}
	//int k = this->Get2DPosition().x - 226 - 50 * m_col;
	//if (abs(k) >= 4) {
	//	this->Set2DPosition(this->Get2DPosition().x-(int)(k*t*100/abs(k)), this->Get2DPosition().y + int(t * 100));
	//}
	//else {
	//	this->Set2DPosition(226 + 50 * m_col,this->Get2DPosition().y);
	//}

}
PieceType Piece::GetType() {
	return m_type;
}

bool Piece::InRightPosition() {
	if (this->Get2DPosition().x != 226 + m_col * 50) return false;
	if (this->Get2DPosition().y != 226 + m_row * 50) return false;
	return true;

}
//std::string Piece::GetKind()
//{
//	return m_kind;
//}
//
//void Piece::SetKind(std::string kind)
//{
//	m_kind = kind;
//}