#include "Piece.h"

Piece::~Piece()
{
}

Piece::Piece()
{
}

int Piece::GetCol()
{
	return m_Col;
}

void Piece::SetCol(int x)
{
	m_Col = x;
}

int Piece::GetRow()
{
	return m_Row;
}

void Piece::SetRow(int y)
{
	m_Row = y;
}

std::string Piece::GetKind()
{
	return m_Kind;
}

void Piece::SetKind(std::string kind)
{
	m_Kind = kind;
}