#pragma once
#include <list>
#include"Piece.h"

using std::list;

class PieceEQClasses
{
	list<Piece*> m_EQClasses[3][3];
public:
	PieceEQClasses();

	list<Piece*>& getEQClass(short left, short top)
	{
		return m_EQClasses[left + 1][top + 1];
	}

	~PieceEQClasses();
};

