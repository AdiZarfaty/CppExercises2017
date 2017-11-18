#pragma 

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "Piece.h"
#include "BoardErrors.h"

using std::vector;
using std::string;
using std::list;
using std::getline;
using std::stringstream;
using std::cin;

class Board {
	const int m_numberOfPieces;
	vector<Piece*> m_allPieces;  // Board is the owner of all the pieces
	list<Piece*> femaleMale;
	list<Piece*> femaleFemale;
	list<Piece*> femaleFlat;
	list<Piece*> maleMale;
	list<Piece*> maleFemale;
	list<Piece*> maleFlat;
	list<Piece*> flatMale;
	list<Piece*> flatFemale;
	list<Piece*> flatFlat;
	BoardErrors error;
public:
	Board(int numberOfPieces): m_numberOfPieces(numberOfPieces), error(numberOfPieces){
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
	BoardErrors getError() {
		return error;
	}
};

