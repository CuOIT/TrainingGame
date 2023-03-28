#pragma once
#include "Sprite2D.h"

enum class PieceType
{
	HP,
	Mana,
	Poison,
	Shield,
	Spell,
	Sword,
	None
};

class Piece : public Sprite2D
{
private:
	int m_col;
	int m_row;
	PieceType m_type;

public:
	Piece() : Sprite2D(), m_col(0), m_row(0), m_type(PieceType::None) {};
	Piece(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		int row, int col,PieceType piecetype) : Sprite2D(model, shader, texture), m_col(col),m_row(row),m_type(piecetype) {};
	~Piece();

	void SetCol(int x);
	int GetCol();
	void SetRow(int y);
	int GetRow();
	void Dropping(float t);
	bool InRightPosition();

	PieceType GetType();
};