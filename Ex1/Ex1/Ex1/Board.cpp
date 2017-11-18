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
				m_error.wrongID.push_back(id);
				m_error.error = true;
			}
			else
				ids[id - 1]++;
		}
		else {
			m_error.error = true;
			m_error.wrongLineString.push_back(line);
			m_error.wrongLineID.push_back(-1);
			ss.clear();
			ss.ignore();
		}

		for (int j = 0; j < 4; j++) {
			ss >> sides[j];
			if (ss.good()) {
				if (sides[j] != 1 && sides[j] != -1 && sides[j] != 0) {
					m_error.error = true;
					m_error.wrongLineID.push_back(id);
					m_error.wrongLineString.push_back(line);
				}
				else if (sides[j] == 0) {
					switch (j) {
					case 0: m_error.m_numOfStraightEdges_rl++;
					case 1: m_error.m_numOfStraightEdges_tb++;
					case 2: m_error.m_numOfStraightEdges_rl--;
					case 3: m_error.m_numOfStraightEdges_tb--;
					}
				}
				else {
					m_error.m_sumOfEdges += sides[j];
				}

			}
			else {
				m_error.error = true;
				m_error.wrongLineID.push_back(id);
				m_error.wrongLineString.push_back(line);
				ss.clear();
				ss.ignore();
			}
		}
		if (!ss.eof()) {
			m_error.error = true;
			m_error.wrongLineID.push_back(id);
			m_error.wrongLineString.push_back(line);
		}
		if (!m_error.error) {
			m_allPieces[i] = new Piece(id, sides[0], sides[1], sides[2], sides[3]);
		}
	}

	if (!m_error.error)
	{
		setEqualityClasses();
	}
	else
	{
		m_error.sortErrors();
	}
}
void Board::setEqualityClasses() {
	for (Piece *piecePtr : m_allPieces) {
		m_eqClasses.getEQClass(piecePtr->getLeft(), piecePtr->getTop()).push_back(piecePtr);
	}
}