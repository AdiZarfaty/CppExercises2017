#pragma once
#include <list>
#include"Piece.h"

using std::list;

template <class T>
class EQClasses
{
	list<T> m_EQClasses[3][3];
	list<T> m_FrameParts;
	list<T> m_Corners;
public:

	list<T>& getEQClass(short left, short top)
	{
		return m_EQClasses[left + 1][top + 1];
	}

	list<T>& getFrameParts()
	{
		return m_FrameParts;
	}

	list<T>& getCornerParts()
	{
		return m_Corners;
	}
};

