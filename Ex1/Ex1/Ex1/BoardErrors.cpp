#include "stdafx.h"
#include "BoardErrors.h"

bool BoardErrors::hasErrors() const
{
	return m_error;
}

bool BoardErrors::checkCorners()
{
	if (!m_cornerTLexist || !m_cornerTRexist || !m_cornerBLexist || !m_cornerBRexist) {
		m_error = true;
		return false;
	}
	else
		return true;
}

void BoardErrors::sortErrors() {
	sort(m_missingID.begin(), m_missingID.end());
}

void BoardErrors::printErrors(ofstream& outFile) const
{
	if (m_firstLineIsInWrongFormat) {
		outFile << "ERROR: first line is in a wrong format" << endl;
	}
	if (m_couldNotExtractNumElements){
		outFile << "ERROR: could not extract numElements" << endl;
	}

	if (!m_missingID.empty()) {
		outFile << "Missing puzzle element(s) with the following IDs: ";
		for (vector<int>::const_iterator iter = m_missingID.begin(); iter != m_missingID.end(); iter++) {
			if (iter != m_missingID.begin())
				outFile << ", ";
			outFile << *iter;
		}
		outFile << endl;
	}
	if (!m_wrongID.empty()) {
		outFile << "Puzzle of size " << m_numberOfPieces << " cannot have the following IDs: ";
		for (vector<int>::const_iterator iter  = m_wrongID.begin(); iter != m_wrongID.end(); iter++) {
			if (iter != m_wrongID.begin())
				outFile << ", ";
			outFile << *iter;
		}
		outFile << endl;
	}
	if (!m_wrongLineID.empty()) {
		for (unsigned int i = 0; i < m_wrongLineID.size(); i++) {
			outFile << "Puzzle ID " << m_wrongLineID[i] << " has wrong data: " << m_wrongLineString[i];
			outFile << endl;
		}
	}
	if (m_wrongNumberOfStraightEdges)
		outFile << "Cannot solve puzzle: wrong number of straight edges" << endl;
	if(!m_cornerTLexist)
		outFile << "Cannot solve puzzle: missing corner element TL" << endl;
	if (!m_cornerTRexist)
		outFile << "Cannot solve puzzle: missing corner element TR" << endl;
	if (!m_cornerBLexist)
		outFile << "Cannot solve puzzle: missing corner element BL" << endl;
	if (!m_cornerBRexist)
		outFile << "Cannot solve puzzle: missing corner element BR" << endl;
	if(m_wrongSumOfEdges)
		outFile << "Cannot solve puzzle: sum of edges is not zero" << endl;
	if (!m_duplicateID.empty())
		outFile << "ERROR: duplicate ID" << endl; //TODO: check the proper massage
	outFile.close();
}