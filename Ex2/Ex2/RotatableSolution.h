#pragma once
#include "PieceEQClasses.h"
#include "PieceRotationContainer.h"
#include <vector>

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
	bool m_rotationEnabled; //should we try rotation or not

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
	RotatableSolution(int height, int width, EQClasses<PieceRotationContainer>* pieces, bool rotationEnabled) : m_heigt(height), m_width(width), m_rotationEnabled(rotationEnabled), m_Pieces(pieces), m_puzzleSolution(height){

		m_isPieceUsed.resize(height*width, false); // init all pieces as not used

		// setup an empty board
		for (int i = 0; i < m_heigt; i++) //TODO: loop in func should not be in h file
		{
			m_puzzleSolution[i].resize(m_width);
			for (int j = 0; j < m_width; j++) {
				internalAccessPieceRotationContainer(i, j).SetPiece(nullptr);
			}
		}
	}

	~RotatableSolution()
	{

	}

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


