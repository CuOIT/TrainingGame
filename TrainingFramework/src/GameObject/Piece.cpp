#include "Piece.h"

Piece::Piece(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, 
	int col, int row, PieceType type) : Sprite2D(model, shader, texture)
{
	m_position = Vector3(col * 48, row * 48, 0);
	m_col = col;
	m_row = row;
	m_type = type;
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

//std::string Piece::GetKind()
//{
//	return m_kind;
//}
//
//void Piece::SetKind(std::string kind)
//{
//	m_kind = kind;
//}