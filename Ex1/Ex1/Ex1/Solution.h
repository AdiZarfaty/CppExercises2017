#pragma once
#include "Piece.h"
#include "PieceEQClasses.h"
#include <list>

#include <string> //for debug
#include <sstream> // for debug

using std::string; // for debug

using std::list;

class Solution
{
	const int m_heigt;
	const int m_width;

	Piece** m_puzzleSolution; // a 1D array of pointers Piece* for ease of allocation. access to x,y will be via the getter getPiece
	//list<Piece*> m_remainingPieces; // this is the naive solution //TODO: change to EQ classes
	const PieceEQClasses m_remainingPieces;

	Piece*& internalGetPiecePtr(int row, int column) const
	{
		return m_puzzleSolution[row*m_heigt + column];
	}

	// Solve the puzzle for i,j and onward. get a copy of the remaining pieces (by val)
	bool solve(int i, int j, PieceEQClasses remainingPieces); 

	string debugGetSolutionAsString(); // used for debug
public:
	Solution(int height, int width, const PieceEQClasses& pieces): m_heigt(height), m_width(width), m_remainingPieces(pieces){

		// setup an empty board
		m_puzzleSolution = new Piece*[height * width];

		for (int i = 0; i < m_heigt; i++)
		{
			for (int j = 0; j < m_width; j++) {
				internalGetPiecePtr(i, j) = nullptr;
			}
		}
	}

	~Solution()
	{
		delete[] m_puzzleSolution;
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

