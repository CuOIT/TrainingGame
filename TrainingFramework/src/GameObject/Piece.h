#pragma once
#include "Sprite2D.h"

class Piece : Sprite2D
{
private:
	int m_col;
	int m_row;
	std::string m_kind;

public:
	Piece() : Sprite2D(), m_col(0), m_row(0), m_kind("") {}
	~Piece();

	void SetCol(int x);
	int GetCol();
	void SetRow(int y);
	int GetRow();
	void SetKind(std::string kind);
	std::string GetKind();
};