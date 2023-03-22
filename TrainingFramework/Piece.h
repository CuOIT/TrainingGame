#pragma once
#include "Sprite2D.h"

class Piece : Sprite2D
{
private:
	int m_Col;
	int m_Row;
	std::string m_Kind;

public:
	Piece() : Sprite2D(), m_Col(0), m_Row(0), m_Kind("") {}
	~Piece();

	void SetCol(int x);
	int GetCol();
	void SetRow(int y);
	int GetRow();
	void SetKind(std::string kind);
	std::string GetKind();
};