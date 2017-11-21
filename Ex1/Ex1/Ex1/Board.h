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
	int m_numOfStraightEdges_right = 0;
	int m_numOfStraightEdges_left = 0;
	int m_numOfStraightEdges_top = 0;
	int m_numOfStraightEdges_bottom = 0; 

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
	void setCorner(int left, int top, int right, int bottom);
	// Try to solve. if solution exist, put it in m_solution.
	bool solve();

	void writeResponseToFile();
};

