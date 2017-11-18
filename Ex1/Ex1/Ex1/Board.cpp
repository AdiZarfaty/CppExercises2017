#include "stdafx.h"
#include "Board.h"

void Board::readBoard() {
	string line;
	int sides[4];
	int id;
	vector<int> ids(m_numberOfPieces);
	for (int i = 0; i < m_numberOfPieces; i++) {

		getline(cin, line);
		stringstream ss;
		ss << line;

		ss >> id;
		if (ss.good()) {
			if (id < 1 || id > m_numberOfPieces) {
				error.wrongID.push_back(id);
				error.error = true;
			}
			else
				ids[id - 1]++;
		}
		else {
			error.error = true;
			error.wrongLineString.push_back(line);
			error.wrongLineID.push_back(-1);
			ss.clear();
			ss.ignore();
		}

		for (int j = 0; j < 4; j++) {
			ss >> sides[j];
			if (ss.good()) {
				if (sides[j] != 1 && sides[j] != -1 && sides[j] != 0) {
					error.error = true;
					error.wrongLineID.push_back(id);
					error.wrongLineString.push_back(line);
				}
				else if (sides[j] == 0) {
					switch (j) {
					case 0: error.m_numOfStraightEdges_rl++;
					case 1: error.m_numOfStraightEdges_tb++;
					case 2: error.m_numOfStraightEdges_rl--;
					case 3: error.m_numOfStraightEdges_tb--;
					}
				}
				else {
					error.m_sumOfEdges += sides[j];
				}

			}
			else {
				error.error = true;
				error.wrongLineID.push_back(id);
				error.wrongLineString.push_back(line);
				ss.clear();
				ss.ignore();
			}
		}
		if (!ss.eof()) {
			error.error = true;
			error.wrongLineID.push_back(id);
			error.wrongLineString.push_back(line);
		}
		if (!error.error) {
			m_allPieces[i] = new Piece(id, sides[0], sides[1], sides[2], sides[3]);
		}
	}
	if (!error.error)
		setEqualityClasses;
}
void Board::setEqualityClasses() {
	for (Piece *piece : m_allPieces) {
		switch (piece->m_left) {
		case -1:
			switch (piece->m_top) {
			case -1:
				femaleFemale.push_back(piece);
				break;
			case 0:
				femaleFlat.push_back(piece);
				break;
			case 1:
				femaleMale.push_back(piece);
				break;
			}
			break;
		case 0:
			switch (piece->m_top) {
			case -1:
				flatFemale.push_back(piece);
				break;
			case 0:
				flatFlat.push_back(piece);
				break;
			case 1:
				flatMale.push_back(piece);
				break;
			}
			break;
		case 1:
			switch (piece->m_top) {
			case -1:
				maleFemale.push_back(piece);
				break;
			case 0:
				maleFlat.push_back(piece);
				break;
			case 1:
				maleMale.push_back(piece);
				break;
			}
			break;
		}
	}
}