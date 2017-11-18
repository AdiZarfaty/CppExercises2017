#pragma 

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "Piece.h"
#include "BoardErrors.h"
#include "PieceEQClasses.h"
#include "Solution.h"

using std::vector;
using std::string;
using std::list;
using std::getline;
using std::stringstream;
using std::cin;

class Board {
	const int m_numberOfPieces;
	vector<Piece*> m_allPieces;  // Board is the owner of all the pieces
	PieceEQClasses m_eqClasses;
	BoardErrors m_error;
	Solution* m_solution;


	void setEqualityClasses();
public:
	Board(int numberOfPieces): m_numberOfPieces(numberOfPieces), m_error(numberOfPieces){
		m_allPieces.reserve(numberOfPieces);
		m_solution = nullptr;
	}

	virtual ~Board() {
		// free all pieces
		for (Piece* piece : m_allPieces) {
			delete piece;
		}

		delete m_solution;
	}

	void readBoard(string filePath);

	bool solve();

	void writeResponseToFile(string filePath) const;

	const BoardErrors& getError() const {
		return m_error;
	}
};

