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
	ifstream* m_inFilePtr; // not owned by board
	ofstream* m_outFilePtr; // not owned by board
	int m_numberOfPieces;
	vector<Piece*> m_allPieces;  // Board is the owner of all the pieces
	EQClasses<PieceRotationContainer> m_eqClasses;
	BoardErrors m_error;
	RotatableSolution* m_solution;
	int m_numOfStraightEdges = 0;

	// fill the EQClasses with the pieces
	void setEqualityClasses();
public:
	Board(ifstream* inFilePtr, ofstream* outFilePtr): m_inFilePtr(inFilePtr), m_outFilePtr(outFilePtr){
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
	void setCorner();
	// Try to solve. if solution exist, put it in m_solution.
	bool solve();

	void writeResponseToFile();
};

