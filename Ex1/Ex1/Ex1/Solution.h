#pragma once
#include "Board.h"
#include "Piece.h"
#include <list>

#include <string> //for debug
#include <sstream> // for debug

using std::list;

class Solution
{
	int m_heigt;
	int m_width;
	Board* m_board;
	Piece** m_puzzleSolution; // a 1D array of pointers Piece* for ease of allocation. access to x,y will be via the getter getPiece
	list<Piece*> m_remainingPieces; // this is the naive solution //TODO: change to EQ classes

	Piece*& internalGetPiece(int line, int row)
	{
		return m_puzzleSolution[line*m_heigt + row];
	}

	bool solve(int i, int j); // Solve the puzzle for i,j and onward.

	string debugGetSolutionAsString(); // used for debug
public:
	Solution(int height, int width): m_heigt(height), m_width(width){

		// setup an empty board
		m_puzzleSolution = new Piece*[height * width];

		for (int i = 0; i < m_heigt; i++)
		{
			for (int j = 0; j < m_width; j++) {
				internalGetPiece(i, j) = nullptr;
			}
		}
	}

	~Solution()
	{
		delete[] m_puzzleSolution;
	}

	bool solve(); // Solve the puzzle

	// API to read the solution
	const Piece* getPiece(int line, int row)
	{
		return m_puzzleSolution[line*m_heigt + row];
	}
};

