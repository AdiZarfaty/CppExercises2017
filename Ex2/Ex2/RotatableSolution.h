#pragma once
#include "PieceEQClasses.h"
#include "PieceRotationContainer.h"
#include <vector>
#include "SolutionFoundChecker.h"

#ifdef DEBUG_SHOW_PROGRESS
#include <string> //for debug
#include <sstream> // for debug
#include <iostream> // for debug
#include <ctime> // for debug
#include <math.h> // for debug
#include <thread> // for write to screen sync in debug
#include <mutex> // for write to screen sync in debug
using std::string; // for debug
using std::cout;
using std::endl;
#endif

using std::vector;


class RotatableSolution
{
	const int m_heigt;
	const int m_width;
	SolutionFoundChecker* m_solutionWasAlreadyFound_ptr;

	EQClasses<PieceRotationContainer>* m_Pieces;
	vector<vector<PieceRotationContainer>> m_puzzleSolution;

	vector<bool> m_isPieceUsed;

	const PieceRotationContainer internalGetPieceRotationContainer(int row, int column) const
	{
		return m_puzzleSolution.at(row).at(column);
	}

	PieceRotationContainer& internalAccessPieceRotationContainer(int row, int column)
	{
		return m_puzzleSolution.at(row).at(column);
	}

	// Solve the puzzle for i,j and onward. get a copy of the remaining pieces (by val)
	bool solve(int i, int j);

	bool isPieceUsed(const PieceRotationContainer& piece) const
	{
		return m_isPieceUsed[piece.getId() - 1];
	}

	void setPieceAsUsed(const PieceRotationContainer& piece, bool newVal)
	{
		m_isPieceUsed[piece.getId() - 1] = newVal;
	}

	// Debug info
	#ifdef DEBUG_SHOW_PROGRESS
	vector<vector<int>> m_optionsCounter;
	vector<vector<int>> m_triedSolutionCounter;
	string debugGetSolutionAsString(int i, int j, int pieceTryiesCounter, int optionListLength); // used for debug
	#endif
	// end debug info


public:
	RotatableSolution(int height, int width, EQClasses<PieceRotationContainer>* pieces, SolutionFoundChecker* solFoundCheck);

	// Solve the puzzle
	bool solve();

	// API to read the solution
	const PieceRotationContainer getPieceRotationContainer(int row, int column) const
	{
		if ((row < 0)
			|| (row >= m_heigt)
			|| (column < 0)
			|| (column >= m_width)) {
			return PieceRotationContainer();
		}

		return internalGetPieceRotationContainer(row, column);
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


