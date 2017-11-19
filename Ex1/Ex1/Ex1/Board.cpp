#include "stdafx.h"
#include "Board.h"

void Board::readBoard() {

	//read first line of file and extract numElements
	string line;
	stringstream ss;
	getline(*m_inFile, line, '=');
	if (line != "NumElements") {
		m_error.setFirstLineIsInWrongFormat();
	}
	int numElements; ss >> numElements;
	if (ss.good()) {
		m_numberOfPieces = numElements;
		m_allPieces.reserve(numElements);
		m_error.setNumberOfPieces(numElements);
		//read the rest of the file and create the board
		int sides[4];
		int id;
		vector<int> ids(m_numberOfPieces);
		for (int i = 0; i < m_numberOfPieces; i++) {

			getline(*m_inFile, line);
			ss << line;

			ss >> id;
			if (ss.good()) {
				if (id < 1 || id > m_numberOfPieces) {
					m_error.m_wrongID.push_back(id);
					m_error.m_error = true;
				}
				else
					ids[id - 1]++;
			}
			else {
				m_error.m_error = true;
				m_error.m_wrongLineString.push_back(line);
				m_error.m_wrongLineID.push_back(-1);
				ss.clear();
				ss.ignore();
			}

			for (int j = 0; j < 4; j++) {
				ss >> sides[j];
				if (ss.good()) {
					if (sides[j] != 1 && sides[j] != -1 && sides[j] != 0) {
						m_error.m_error = true;
						m_error.m_wrongLineID.push_back(id);
						m_error.m_wrongLineString.push_back(line);
					}
					else if (sides[j] == 0) {
						switch (j) {
						case 0: m_numOfStraightEdges_rl++;
						case 1: m_numOfStraightEdges_tb++;
						case 2: m_numOfStraightEdges_rl++;
						case 3: m_numOfStraightEdges_tb++;
						}
					}
					else {
						m_error.sumOfEdges() += sides[j];
					}

				}
				else {
					m_error.m_error = true;
					m_error.m_wrongLineID.push_back(id);
					m_error.m_wrongLineString.push_back(line);
					ss.clear();
					ss.ignore();
				}
			}
			if (!ss.eof()) {
				m_error.m_error = true;
				m_error.m_wrongLineID.push_back(id);
				m_error.m_wrongLineString.push_back(line);
			}
			if (!m_error.m_error) {
				m_allPieces[i] = new Piece(id, sides[0], sides[1], sides[2], sides[3]);
			}
		}
		m_inFile->close();
		if (!m_error.m_error)
		{
			setEqualityClasses();
		}
		else
		{
			m_error.sortErrors();
		}
	}
	else {
		m_error.m_error = true;
		m_error.m_couldNotExtractNumElements = true;
	}

	// an odd number means no solution for sure
	if (((m_numOfStraightEdges_rl % 2) > 0)
		|| ((m_numOfStraightEdges_tb % 2) > 0))
	{
		m_error.m_wrongNumberOfStraightEdges = true;
		m_error.m_error = true;
	}
}

void Board::setEqualityClasses() {
	for (Piece *piecePtr : m_allPieces) {
		m_eqClasses.getEQClass(piecePtr->getLeft(), piecePtr->getTop()).push_back(piecePtr);
	}
}

bool Board::solve()
{
	if (m_error.hasErrors())
	{
		return false;
	}

	int columns;
	bool success = false;
	bool numOfStraightEdgesWasOkAtLeastOnce = false;

	for (int rows = 1; rows <= m_numberOfPieces; rows++)
	{
		if ((m_numberOfPieces % rows) > 0)
		{
			continue; // no such board exist
		}

		columns = m_numberOfPieces / rows;		

		// this helps us avoid trying a solution that is impossible, we are requiered to report it by note 6
		if ((m_numOfStraightEdges_rl >= (rows * 2))
			&& (m_numOfStraightEdges_tb >= (columns * 2)))
		{
			numOfStraightEdgesWasOkAtLeastOnce = true;

			m_solution = new Solution(rows, columns, m_eqClasses);

			success = m_solution->solve();

			if (success)
			{
				break;
			}
			else
			{
				delete m_solution;
				m_solution = nullptr;
			}
		}
	}

	if (!numOfStraightEdgesWasOkAtLeastOnce)
	{
		m_error.m_wrongNumberOfStraightEdges = true;
		m_error.m_error = true;
	}

	return success;
}

void Board::writeResponseToFile()
{
	if (m_error.m_error)
	{
		m_error.printErrors(*m_outFile);
	}
	else
	{
		if (m_solution == nullptr)
		{
			*m_outFile << "Cannot solve puzzle: it seems that there is no proper solution" << endl;
		}
		else
		{
			for (int row = 0; row < (m_solution->getHeight()); row++)
			{
				for (int column = 0; column < (m_solution->getWidth()); column++)
				{
					*m_outFile << m_solution->getPiecePtr(row, column);
					if (column < (m_solution->getWidth() - 1))
					{
						*m_outFile << " ";
					}
				}

				*m_outFile << endl;
			}
		}
	}
}
