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
	ifstream* m_inFile;
	ofstream* m_outFile;
	int m_numberOfPieces;
	vector<Piece*> m_allPieces;  // Board is the owner of all the pieces
	PieceEQClasses m_eqClasses;
	BoardErrors m_error;
	Solution* m_solution;
	int m_numOfStraightEdges_rl = 0; // a counter for the number of striaght edges in Left and right
	int m_numOfStraightEdges_tb = 0; // a counter for the number of striaght edges in Top and Bottom

	// fill the EQClasses with the pieces
	void setEqualityClasses();
public:
	Board(ifstream* inFile, ofstream* outFile): m_inFile(inFile), m_outFile(outFile){
		m_solution = nullptr;
	}

	virtual ~Board() {
		// free all pieces
		for (Piece* piece : m_allPieces) {
			delete piece;
		}

		delete m_solution;
	}

	void readBoard();

	// Try to solve. if solution exist, put it in m_solution.
	bool solve();

	void writeResponseToFile();
};

