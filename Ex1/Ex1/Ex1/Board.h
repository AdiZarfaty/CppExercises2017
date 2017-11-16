#pragma once
#include <vector>
#include <list>
#include "Piece.h"

using std::vector;
using std::string;
using std::list;

class Board {
	const int m_numberOfPieces;
	vector<Piece*> m_allPieces;  // Board is the owner of all the pieces

	int m_sumOfEdges;
	int m_numOfStraightEdges_right;
	int m_numOfStraightEdges_left;
	int m_numOfStraightEdges_top;
	int m_numOfStraightEdges_bottom;

	// TODO: should be in BoardErrors
	bool error;
	vector<int> missingID;
	vector<int> wrongID;
	vector<int> wrongLineID;
	vector<string> wrongLineString;

	list<Piece*> cornerTL; //TODO: I think there is no need for TL,TR,T,L these are included in the EQ classes.. we should just write these
	list<Piece*> cornerTR;
	list<Piece*> cornerbL;
	list<Piece*> cornerBR;
	list<Piece*> borderTop;
	list<Piece*> borderBottom;
	list<Piece*> borderLeft;
	list<Piece*> borderRight;
public:
	Board(int numberOfPieces): m_numberOfPieces(numberOfPieces){
		m_allPieces.reserve(numberOfPieces);
		m_sumOfEdges = 0;
		m_numOfStraightEdges_right = 0;
		m_numOfStraightEdges_left = 0;
		m_numOfStraightEdges_top = 0;
		m_numOfStraightEdges_bottom = 0;
	}

	virtual ~Board() {
		// free all pieces
		for (Piece* piece : m_allPieces) {
			delete piece;
		}
	}

	void readBoard();
	void setBoard();     
	void setCorners();   
	void setBorders();   
	//bool[] hasCorners; //TODO: what is this ?
};

