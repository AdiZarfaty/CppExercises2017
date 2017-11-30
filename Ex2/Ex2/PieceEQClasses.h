#pragma once
#include <list>
#include"Piece.h"

using std::list;

template <class T>
class EQClasses //TODO: ADI instead of list<Piece*> we will use RotationContainer class - I am using templates instead
{
	list<T> m_EQClasses[3][3];
public:

	list<T>& getEQClass(short left, short top)
	{
		return m_EQClasses[left + 1][top + 1];
	}
};

