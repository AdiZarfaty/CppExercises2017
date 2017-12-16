
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
						else if (sides[j] == 0)
						{
							m_numOfStraightEdges++;

							switch (j){
							case 0: m_numOfStraightEdges_left++;
								break;
							case 1: m_numOfStraightEdges_top++;
								break;
							case 2: m_numOfStraightEdges_right++;
								break;
							case 3: m_numOfStraightEdges_bottom++;
							}

						}
						else {
							m_sumOfEdges += sides[j];
						}
					}
					else 
					{
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
					Piece newPiece(id, sides[0], sides[1], sides[2], sides[3]);
					m_allPieces.push_back(newPiece);
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

		if (m_rotationEnabled)
		{
			if ((m_numOfStraightEdges % 2) != 0) 
			{
				m_error.setWrongNumberOfStraightEdges();
			}
		}
		else
		{
			if ((m_numOfStraightEdges_right != m_numOfStraightEdges_left)
				|| (m_numOfStraightEdges_top != m_numOfStraightEdges_bottom))
			{
				m_error.setWrongNumberOfStraightEdges();
			}
		}

		if (m_sumOfEdges != 0) {
			m_error.setWrongSumOfEdges();
		}
		for (int i = 0; i < m_numberOfPieces; i++) {
			if (ids[i] == 0) {
				m_error.addMissingID(i + 1);
			}
		}

		m_error.sortMissingIDErrors();

		setEqualityClasses();

		if (m_rotationEnabled) 
		{
			checkCornersExistRotational();
		}
		else
		{
			checkCornersExistNonRotational();
		}
		

	}
	else {
		m_error.setCouldNotExtractNumElements();
	}

}

void Board::setNonRotateCornerAsFound(int left, int top, int right, int bottom) {
	if (m_error.getMissingCorners().size() == 0)
	{
		return; // no need to run
	}

	string corner = "";

	if (top == 0 && left == 0) {
		corner = "TL";
	}
	if (top == 0 && right == 0) {
		corner = "TR";
	}
	if (bottom == 0 && left == 0) {
		corner = "BL";
	}
	if (bottom == 0 && right == 0) {
		corner = "BR";
	}

	if (corner != "")
	{
		vector<string>::iterator result = std::find(m_error.getMissingCorners().begin(), m_error.getMissingCorners().end(), corner);
		if (result != m_error.getMissingCorners().end())
		{
			m_error.getMissingCorners().erase(result);
		}
	}
}

void Board::checkCornersExistNonRotational() {
	for (PieceRotationContainer rc : m_eqClasses.getCornerParts())
	{
		setNonRotateCornerAsFound(rc.getLeft(), rc.getTop(), rc.getRight(), rc.getBottom());
	}
	if (m_error.getMissingCorners().size() == 0)
	{
		m_error.setFourCorners();
	}
	if (m_eqClasses.getThreeStraightEdges().size() >= 2) {
		m_error.setTwoCorners();
	}
	m_error.checkCorners();
}

void Board::checkCornersExistRotational() {
	if (m_eqClasses.getCornerParts().size() >= 4) {
		m_error.setFourCorners();
		m_error.getMissingCorners().clear();
	}
	else {
		for (unsigned int i = 0; i < m_eqClasses.getCornerParts().size(); i++) {
			m_error.getMissingCorners().pop_back(); // so that the count will reflect how many corners are missing
		}
	}
	/*check if there are atleast 2 pieces with 3 straight edges, 
	which can make for the 2 corners of a single line solution*/
	if (m_eqClasses.getThreeStraightEdges().size() >= 2) {
		m_error.setTwoCorners();
	}
	m_error.checkCorners();
}

void Board::setEqualityClasses() {
	for (vector<Piece>::iterator it = m_allPieces.begin(); it != m_allPieces.end(); ++it) {

		int maxRotation;
		if (m_rotationEnabled)
		{
			maxRotation = 4;
		}
		else
		{
			maxRotation = 1;
		}

		for (int i = 0; i < maxRotation; i++) {
			PieceRotationContainer rc = PieceRotationContainer(&(*it), i * 90); //pass a pointer to the piece
			m_eqClasses.getEQClass(rc.getLeft(), rc.getTop()).push_back(rc);
		}

		bool isEdge = false;
		bool isCorner = false;
		bool isThreeStraightEdges = false;

		for (int i = 0; i < 4; i++) {
			if (it->getFace(i) == 0)
			{
				isEdge = true;
				if (it->getFace((i + 1) % 4) == 0)
				{
					isCorner = true;
					if (it->getFace((i + 2) % 4) == 0)
					{
						isThreeStraightEdges = true;
						break; // no need to try other rotations. got the max result
					}
				}
			}
		}

		PieceRotationContainer rc = PieceRotationContainer(&(*it), 0);

		if (isThreeStraightEdges)
		{
			m_eqClasses.getThreeStraightEdges().push_back(rc); // save every piece just once in these list
		}

		if (isCorner)
		{
			m_eqClasses.getCornerParts().push_back(rc); // save every piece just once in these list
		}

		if (isEdge)
		{
			m_eqClasses.getFrameParts().push_back(rc); // save every piece just once in these list
		}
	}
}

bool Board::IsEnoughEdgesAndCornersAvailableToTrySolutionOfSize(int rows, int columns)
{
	if (!m_rotationEnabled)
	{
		if ((m_numOfStraightEdges_right < rows)
			|| (m_numOfStraightEdges_top < columns))  // left/bottom are symetric
		{
			return false;
		}
	}

	// calc the needed pieces to build the frame.
	unsigned int neededCornersCount;
	unsigned int neededFramePartsCount;
	if ((rows == 1) || (columns == 1))
	{
		neededCornersCount = 2;
		neededFramePartsCount = std::max(rows, columns);
	}
	else
	{
		neededCornersCount = 4;
		neededFramePartsCount = rows*columns - ((rows - 2) * (columns - 2));
	}

	if ((m_eqClasses.getFrameParts().size() < neededFramePartsCount)
		|| (m_eqClasses.getCornerParts().size() < neededCornersCount))
	{
		return false;
	}

	return true;
}

bool Board::solve() //TODO: consider building frame first. need to tweek solve(i,j) as well to check if fits to right and bottom (if they are filled)
{
	if (m_error.hasErrors())
	{
		return false;
	}

	bool success = false;
	bool numOfStraightEdgesWasOkAtLeastOnce = false;

	for (int rows = 1; rows <= m_numberOfPieces; rows++)
	{
		if ((m_numberOfPieces % rows) > 0)
		{
			continue; // no such board exist
		}

		int columns = m_numberOfPieces / rows;		
		// this helps us avoid trying a solution that is impossible, we are requiered to report it by note 6
		if (!IsEnoughEdgesAndCornersAvailableToTrySolutionOfSize(rows, columns))
		{
			continue;
		}

		numOfStraightEdgesWasOkAtLeastOnce = true;

		// no need to release, as next assignment will free the prev, and the last one will be freed in the dtor
		m_solution = std::move(std::make_unique<RotatableSolution>(rows, columns, &m_eqClasses, m_rotationEnabled));

		success = m_solution->solve();

		if (success)
		{
			break;
		}
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
