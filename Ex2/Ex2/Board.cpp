
#include "Board.h"

void Board::readBoard() {

	//read first line of file and extract numElements
	string line;
	bool error;
	stringstream ss;
	getline(*m_inFilePtr, line, '=');
	ss = stringstream(line);
	ss >> line;
	if (line != "NumElements") {
		m_error.setFirstLineIsInWrongFormat();
	}
	getline(*m_inFilePtr, line);
	ss = stringstream(line);
	int numElements; ss >> numElements;
	if (!ss.fail()) { //got the number
		m_numberOfPieces = numElements;
		m_allPieces.reserve(numElements);
		m_error.setNumberOfPieces(numElements);
		//read the rest of the file and create the board
		int sides[4];
		int id;
		vector<int> ids(m_numberOfPieces);
		for (int i = 0; i < numElements; i++) {
			error = false; //error in this specific piece
			if (m_inFilePtr->eof()) {
				break;
			}
			getline(*m_inFilePtr, line);
			ss = stringstream(line);
			if (line == "") {
				i--;
				continue;
			}
			ss >> id;
			if (!ss.fail()) {
				if (id < 1 || id > m_numberOfPieces) {
					m_error.addWrongID(id);
					continue;
				}
				else {//already seen this id
					ids[id - 1]++;
					if (ids[id - 1] > 1) {
						m_error.addWrongLine(id, line);
						continue;
					}
				}
				for (int j = 0; j < 4; j++) {
					ss >> sides[j];
					if (!ss.fail()) {
						if (sides[j] != 1 && sides[j] != -1 && sides[j] != 0) {
							m_error.addWrongLine(id, line);
							error = true;
							break;
						}
						else if (sides[j] == 0) {
							if (m_rotationEnabled) {
								m_numOfStraightEdges++;
							}
							else {
								switch (j) {
								case 0: m_numOfStraightEdges_left++;
									break;
								case 1: m_numOfStraightEdges_top++;
									break;
								case 2: m_numOfStraightEdges_right++;
									break;
								case 3: m_numOfStraightEdges_bottom++;
								}
							}
						}
						else {
							m_error.sumOfEdges() += sides[j];
						}
						if (j == 3 && ss.eof() && !m_rotationEnabled)
							setCorner(sides[0], sides[1], sides[2], sides[3]);
					}
					else {
						m_error.addWrongLine(id, line);
						error = true;
						break;
					}
				}
				if (!ss.eof() && error == false) {
					string tmp; ss >> tmp;
					if (!ss.fail()) {
						m_error.addWrongLine(id, line);
						break;
					}
				}
				if (!m_error.hasErrors()) {
					Piece* newPiecePtr = new Piece(id, sides[0], sides[1], sides[2], sides[3]);
					m_allPieces.push_back(newPiecePtr);
				}
			}
			else {//if id is a string add a similar error to that of wrong id, but not the same one.
				ss = stringstream(line);
				string id_str; ss >> id_str;
				if (!ss.fail()) {
					m_error.addNonIntID(id_str);
				}
				else {
					m_error.addWrongLine(-1, line);
				}
			}
		}
		m_inFilePtr->close();
		if (m_numOfStraightEdges % 2 != 0 && m_rotationEnabled) {
			m_error.setWrongNumberOfStraightEdges();
		}
		if ((m_numOfStraightEdges_right - m_numOfStraightEdges_left != 0
			|| m_numOfStraightEdges_top - m_numOfStraightEdges_bottom != 0) && m_rotationEnabled) {
			m_error.setWrongNumberOfStraightEdges();
		}
		if (m_error.sumOfEdges() != 0) {
			m_error.setWrongSumOfEdges();
		}
		for (int i = 0; i < m_numberOfPieces; i++) {
			if (ids[i] == 0) {
				m_error.addMissingID(i + 1);
			}
		}
		if (!m_error.hasErrors())
		{
			if (m_rotationEnabled) {
				setCornerRotational();
			}
			setEqualityClasses();
		}
		else
		{
			m_error.sortErrors();
		}
	}
	else {
		m_error.setCouldNotExtractNumElements();
	}

}

void Board::setCorner(int left, int top, int right, int bottom) {
	if (top == 0 && left == 0) {
		m_error.getMissingCorners().erase(m_error.getMissingCorners().begin()+0);
	}
	if (top == 0 && right == 0) {
		m_error.getMissingCorners().erase(m_error.getMissingCorners().begin() + 1);
	}
	if (bottom == 0 && left == 0) {
		m_error.getMissingCorners().erase(m_error.getMissingCorners().begin() + 2);
	}
	if (bottom == 0 && right == 0) {
		m_error.getMissingCorners().erase(m_error.getMissingCorners().begin() + 3);
	}
}

void Board::setCornerRotational() {
	int count = 0;
	if (m_eqClasses.getEQClass(0,0).size() >= 4) {
		m_error.setFourCorners();
		m_error.getMissingCorners() = {};
	}
	else {
		for (int i = 0; i < m_eqClasses.getEQClass(0, 0).size(); i++) {
			m_error.getMissingCorners().pop_back();
		}
	}
	/*check if there are atleast 2 pieces with 3 straight edges, 
	which can make for the 2 corners of a single line solution*/
	for (PieceRotationContainer rc : m_eqClasses.getEQClass(0, 0)) {
		if (rc.getRight() == 0 || rc.getBottom() == 0) {
			count++;
			if (count = 2) {
				m_error.setTwoCorners();
				break;
			}
		}
	}
	m_error.checkCorners();
}

void Board::setEqualityClasses() {
	if (m_rotationEnabled) {
		for (Piece *piecePtr : m_allPieces) {
			PieceRotationContainer rc = PieceRotationContainer(piecePtr, 0);
			m_eqClasses.getEQClass(rc.getLeft(), rc.getTop()).push_back(rc);
		}
	}
	else {
		for (Piece *piecePtr : m_allPieces) {
			for (int i = 0; i < 4; i++) {
				PieceRotationContainer rc = PieceRotationContainer(piecePtr, i);
				m_eqClasses.getEQClass(rc.getLeft(), rc.getTop()).push_back(rc);
			}
		}
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
		//TODO: ADI no longer relevant
		// this helps us avoid trying a solution that is impossible, we are requiered to report it by note 6


		//if ((m_numOfStraightEdges_right >= (rows))
		//	&& (m_numOfStraightEdges_top >= (columns)))
		//{

		//TODO: Still need to fix number of straight edges test

			numOfStraightEdgesWasOkAtLeastOnce = true;

			m_solution = new RotatableSolution(rows, columns, &m_eqClasses, m_rotationEnabled);

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
		//}
		
	}

	if (!numOfStraightEdgesWasOkAtLeastOnce)
	{
		m_error.setWrongNumberOfStraightEdges();
	}

	return success;
}

void Board::writeResponseToFile() const
{
	ofstream& outstream = *m_outFilePtr;
	if (m_error.hasErrors())
	{
		m_error.printErrors(outstream, m_rotationEnabled);
	}
	else
	{
		if (m_solution == nullptr)
		{
			outstream << "Cannot solve puzzle: it seems that there is no proper solution" << endl;
		}
		else
		{
			for (int row = 0; row < (m_solution->getHeight()); row++)
			{
				for (int column = 0; column < (m_solution->getWidth()); column++)
				{
					const PieceRotationContainer& rc = m_solution->getPieceRotationContainer(row, column);
					outstream << rc.getId();

					if (rc.getRotationAngle() > 0)
					{
						outstream << " [" << rc.getRotationAngle() << "]";
					}

					if (column < (m_solution->getWidth() - 1))
					{
						outstream << " ";
					}
				}

				outstream << endl;
			}
		}
	}

	outstream.flush();	
}
