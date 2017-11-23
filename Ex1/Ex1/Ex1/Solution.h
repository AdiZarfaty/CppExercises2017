#pragma once
#include "Piece.h"
#include "PieceEQClasses.h"
#include <vector>
#include <string> //for debug
#include <sstream> // for debug

using std::string; // for debug
using std::vector;

class Solution
{
	const int m_heigt;
	const int m_width;

	vector<vector<Piece*>> m_puzzleSolution;
	PieceEQClasses* m_Pieces;

	const Piece* internalGetPiecePtr(int row, int column) const
	{
		return m_puzzleSolution.at(row).at(column);
	}

	Piece*& internalAccessPiecePtr(int row, int column)
	{
		return m_puzzleSolution.at(row).at(column);
	}

	// Solve the puzzle for i,j and onward. get a copy of the remaining pieces (by val)
	bool solve(int i, int j, PieceEQClasses remainingPieces); 

	string debugGetSolutionAsString(); // used for debug
public:
	Solution(int height, int width, PieceEQClasses* pieces): m_heigt(height), m_width(width), m_Pieces(pieces), m_puzzleSolution(height){

		// setup an empty board
		for (int i = 0; i < m_heigt; i++)
		{
			m_puzzleSolution[i].resize(m_width);
			for (int j = 0; j < m_width; j++) {
				internalAccessPiecePtr(i, j) = nullptr;
			}
		}
	}

	~Solution()
	{

	}

	bool solve(); // Solve the puzzle

	// API to read the solution
	const Piece* getPiecePtr(int row, int column) const
	{
		if ((row < 0)
			|| (row >= m_heigt)
			|| (column < 0)
			|| (column >= m_width)){
			return nullptr;
		}

		return internalGetPiecePtr(row, column);
	}

	int getHeight() const
	{
		return m_heigt;
	}

	int getWidth() const
	{
		return m_width;
	}
};

