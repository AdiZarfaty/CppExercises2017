#pragma once
#include <list>
#include"Piece.h"

using std::list;

template <class T>
class EQClasses
{
	list<T> m_EQClasses[3][3]; //including rotation permutation if board rotatable
	list<T> m_FrameParts; //unrotated
	list<T> m_TwoStraightEdges; //unrotated
	list<T> m_ThreeStraightEdges; //unrotated
public:
	//get a list of parts that match the left-top pattern. including rotation permutation if board rotatable
	list<T>& getEQClass(short left, short top)
	{
		return m_EQClasses[left + 1][top + 1];
	}

	//unrotated
	list<T>& getFrameParts()
	{
		return m_FrameParts;
	}

	//unrotated
	list<T>& getCornerParts()
	{
		return m_TwoStraightEdges;
	}

	//unrotated
	list<T>& getThreeStraightEdges()
	{
		return m_ThreeStraightEdges;
	}
};

