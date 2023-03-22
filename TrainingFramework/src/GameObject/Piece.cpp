#include "Piece.h"

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

std::string Piece::GetKind()
{
	return m_kind;
}

void Piece::SetKind(std::string kind)
{
	m_kind = kind;
}