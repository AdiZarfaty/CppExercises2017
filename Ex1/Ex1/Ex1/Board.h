#pragma 

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "Piece.h"
#include "BoardErrors.h"
#include "PieceEQClasses.h"

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
public:
	Board(int numberOfPieces): m_numberOfPieces(numberOfPieces), m_error(numberOfPieces){
		m_allPieces.reserve(numberOfPieces);
	}

	virtual ~Board() {
		// free all pieces
		for (Piece* piece : m_allPieces) {
			delete piece;
		}
	}

	void readBoard();

	void setEqualityClasses();

	const BoardErrors& getError() {
		return m_error;
	}
};

