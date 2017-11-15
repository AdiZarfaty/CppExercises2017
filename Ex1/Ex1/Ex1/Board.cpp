#include "stdafx.h"
#include "Board.h"

/*
void Board::readBoard() {
	bool e;
	string line;
	int sides[4];
	for (int i = 0; i < numElements; i++) {
		if (e)
			this->error = true;
		e = false;

		getLine(cin, line);
		stringstream ss << line;

		ss >> id;
		if (ss.good()) {
			if (id < 1 || id > numElements) {
				wrongID.push_back(id);
				e = true;
			}
			else
				ids[id + 1]++;
		}
		else {
			e = true;
			wrongLineString.push_back(line);
			wrongLineID.push_back(-1);
			ss.clear();
			ss.ignore();
		}

		for (int j = 0; j < 4; j++) {
			ss >> sides[j];
			if (ss.good()) {
				if (sides[j] != 1 && sides[j] != -1 && sides[j] != 0) {
					e = true;
					wrongLineID.push_back(id);
					wrongLineString.push_back(line);
				}
				else if (sides[j] == 0) {
					switch (j) {
					case 0: numOfStraightEdges_l++;
					case 1: numOfStraightEdges_t++;
					case 2: numOfStraightEdges_r++;
					case 3: numOfStraightEdges_b++;
					}
				}
				else {
					sumOfEdges += sides[j];
				}

			}
			else {
				e = true;
				wrongLineID.push_back(id);
				wrongLineString.push_back(line);
				ss.clear();
				ss.ignore();
			}
		}
		if (!e) {
			board->allPieces[i] = &new Piece(id, left, top, right, bottom);
		}
	}
	setBoard();
}
void Board::setBoard() {
	setCorners();
	setBorders();
	sort(missingID.begin(), missingID.end());
}
void Board::setCorners() {
	Piece *piece;
	for (int i = 0; i < this->n; i++) {
		piece = this->allPieces[i];
		if (piece->getLeft() == 0 && piece->getTop() == 0) {
			cornetTL.push_back(piece);
		}
		if (piece->getright() == 0 && piece->getTop() == 0) {
			cornetTR.push_back(piece);
		}
		if (piece->getLeft() == 0 && piece->getBottom() == 0) {
			cornetBL.push_back(piece);
		}
		if (piece->getRight() == 0 && piece->getBottom() == 0) {
			cornetBR.push_back(piece);
		}
	}
}
void Board::setBorders() {
	Piece *piece;
	for (int i = 0; i < this->n; i++) {
		piece = this->allPieces[i];
		if (piece->getLeft() == 0) {
			borderLeft.push_back(piece);
		}
		if (piece->getright() == 0) {
			borderRight.push_back(piece);
		}
		if (piece->getTop() == 0) {
			borderTop.push_back(piece);
		}
		if (piece->getBottom() == 0) {
			borderBottom.push_back(piece);
		}
	}
}
bool * Board::hasCorners() {
	static bool corners[4];
	if (!this.cornerTL.empty())
		bool[0] = true;
	if (!this.cornerTR.empty())
		bool[1] = true;
	if (!this.cornerBL.empty())
		bool[2] = true;
	if (!this.cornerBR.empty())
		bool[3] = true;
	return corners;
}
*/