#pragma once

#include <sstream>
#include <list>
#include "Piece.h"
#include "BoardErrors.h"
#include "PieceEQClasses.h"
#include "Solution.h"
#include "RotatableSolution.h"
#include "PieceRotationContainer.h"

using std::vector;
using std::string;
using std::list;
using std::getline;
using std::stringstream;
using std::ifstream;
using std::cerr;
using std::to_string;

class Board {
	bool m_rotationEnabled; //should we try rotation or not
	int m_numOfStraightEdges_right = 0;
	int m_numOfStraightEdges_left = 0;
	int m_numOfStraightEdges_top = 0;
	int m_numOfStraightEdges_bottom = 0;
	ifstream* m_inFilePtr; // not owned by board
	ofstream* m_outFilePtr; // not owned by board
	int m_numberOfPieces;
	vector<Piece*> m_allPieces;  // Board is the owner of all the pieces //TODO: convert to smart pointers
	EQClasses<PieceRotationContainer> m_eqClasses;
	BoardErrors m_error;
	RotatableSolution* m_solution;
	int m_numOfStraightEdges = 0; //num of all straight edges in all the pieces
	int m_sumOfEdges = 0; //the sum of all the edges of all the pieces

	// fill the EQClasses with the pieces
	void setEqualityClasses();

	bool IsEnoughEdgesAndCornersAvailableToTrySolutionOfSize(int rows, int columns);
public:
	Board(ifstream* inFilePtr, ofstream* outFilePtr, bool rotationEnabled): m_inFilePtr(inFilePtr), m_outFilePtr(outFilePtr), m_rotationEnabled(rotationEnabled){
		m_solution = nullptr;
	}

	virtual ~Board() {
		// free all pieces
		for (Piece* piece : m_allPieces) {
			delete piece;
		}

		if (m_solution != nullptr)
		{
			delete m_solution;
		}
	}

	void readBoard();
	void setCorner(int left, int top, int right, int bottom);
	void setCornerRotational();
	void setCornerNonRotational();
	// Try to solve. if solution exist, put it in m_solution.
	bool solve();

	void writeResponseToFile() const;
};

