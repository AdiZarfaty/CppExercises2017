#pragma once
#include "PieceEQClasses.h"
#include "PieceRotationContainer.h"
#include <vector>
#include <string> //for debug
#include <sstream> // for debug
#include <iostream> // for debug
#include <ctime> // for debug

using std::string; // for debug
using std::vector;

using std::cout;
using std::endl;

class RotatableSolution
{
	const int m_heigt;
	const int m_width;
	bool m_rotationEnabled; //should we try rotation or not

	EQClasses<PieceRotationContainer>* m_Pieces;
	vector<vector<PieceRotationContainer>> m_puzzleSolution;

	const PieceRotationContainer internalGetPiecePtr(int row, int column) const
	{
		return m_puzzleSolution.at(row).at(column);
	}

	PieceRotationContainer& internalAccessPiecePtr(int row, int column)
	{
		return m_puzzleSolution.at(row).at(column);
	}

	// Solve the puzzle for i,j and onward. get a copy of the remaining pieces (by val)
	bool solve(int i, int j);

	//TODO: remove debug info at the end
	// Debug info
	vector<vector<int>> m_optionsCounter;
	vector<vector<int>> m_triedSolutionCounter;


	string debugGetSolutionAsString(int i, int j, int pieceTryiesCounter, int optionListLength); // used for debug
public:
	RotatableSolution(int height, int width, EQClasses<PieceRotationContainer>* pieces, bool rotationEnabled) : m_heigt(height), m_width(width), m_Pieces(pieces), m_puzzleSolution(height), m_rotationEnabled(rotationEnabled){

		// setup an empty board
		for (int i = 0; i < m_heigt; i++)
		{
			m_puzzleSolution[i].resize(m_width); //TODO: empty creation can be done with resize ? no need for loop to init ?
			for (int j = 0; j < m_width; j++) {
				internalAccessPiecePtr(i, j).SetPiece(nullptr);
			}
		}
	}

	~RotatableSolution()
	{

	}

	bool solve(); // Solve the puzzle

	// API to read the solution
	const PieceRotationContainer getPieceRotationContainer(int row, int column) const
	{
		if ((row < 0)
			|| (row >= m_heigt)
			|| (column < 0)
			|| (column >= m_width)) {
			return PieceRotationContainer();
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


