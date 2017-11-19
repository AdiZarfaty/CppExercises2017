#pragma 

#include <sstream>
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
using std::ifstream;
using std::cerr;

class Board {
	int m_numberOfPieces;
	vector<Piece*> m_allPieces;  // Board is the owner of all the pieces
	PieceEQClasses m_eqClasses;
	BoardErrors m_error;
	Solution* m_solution;


	void setEqualityClasses();
public:
	Board(){
		m_solution = nullptr;
	}

	virtual ~Board() {
		// free all pieces
		for (Piece* piece : m_allPieces) {
			delete piece;
		}

		delete m_solution;
	}

	void readBoard(string, string);

	bool solve(string);

	void writeResponseToFile(string);

	const BoardErrors& getError() const {
		return m_error;
	}
};

