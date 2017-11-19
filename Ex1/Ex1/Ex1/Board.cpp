#include "stdafx.h"
#include "Board.h"

void Board::readBoard(string inputFile, string outputFile) {
	ifstream inFile;
	inFile.open(inputFile);
	if (!inFile) {
		cerr << "ERROR: Unable to open input file " << inputFile << endl;
		exit(1); //check if we can use exit;
	}
	ofstream outFile;
	outFile.open(outputFile);
	if (!outFile) {
		cerr << "ERROR: Unable to open output file " << outputFile << endl;
		exit(1); //check if we can use exit
	}
	//read first line of file and extract numElements
	string line;
	stringstream ss;
	getline(inFile, line, '=');
	if (line != "NumElements") {
		 outFile << "ERROR: first line is in a wrong format" << endl;
	}
	int numElements; ss >> numElements;
	if (ss.good()) {
		m_numberOfPieces = numElements;
		m_allPieces.reserve(numElements);
		m_error.m_numberOfPieces = numElements;
		//read the rest of the file and create the board
		int sides[4];
		int id;
		vector<int> ids(m_numberOfPieces);
		for (int i = 0; i < m_numberOfPieces; i++) {

			getline(inFile, line);
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
						case 0: m_numOfStraightEdges_rl++;
						case 1: m_numOfStraightEdges_tb++;
						case 2: m_numOfStraightEdges_rl++;
						case 3: m_numOfStraightEdges_tb++;
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
		inFile.close();
		if (!m_error.error)
		{
			setEqualityClasses();
		}
		else
		{
			m_error.sortErrors();
		}
	}
	else {
		outFile << "ERROR: could not extract numElements";
	}

	// an odd number means no solution for sure
	if (((m_numOfStraightEdges_rl % 2) > 0)
		|| ((m_numOfStraightEdges_tb % 2) > 0))
	{
		m_error.m_wrongNumberOfStraightEdges = true;
		m_error.error = true;
	}

	outFile.close();
}

void Board::setEqualityClasses() {
	for (Piece *piecePtr : m_allPieces) {
		m_eqClasses.getEQClass(piecePtr->getLeft(), piecePtr->getTop()).push_back(piecePtr);
	}
}

bool Board::solve(string filePath)
{
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
		m_error.error = true;
	}

	return success;
}

void Board::writeResponseToFile(string filePath)
{
	if (m_error.error)
		m_error.printErrors(filePath);
	else
		solve(filePath);
}
