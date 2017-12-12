
#include "BoardErrors.h"

bool BoardErrors::hasErrors() const
{
	return m_error;
}

void BoardErrors::checkCorners()
{
	//TODO: need to check with/without rotation
	if (!m_fourCorners && !m_twoCorners) {
		m_error = true;
	}
}

void BoardErrors::sortErrors() {
	sort(m_missingID.begin(), m_missingID.end());
}

void BoardErrors::printErrors(ofstream& outFile, bool rotation) const
{
	if (m_firstLineIsInWrongFormat) {
		outFile << "ERROR: first line is in a wrong format" << endl;
	}
	if (m_couldNotExtractNumElements){
		outFile << "ERROR: could not extract numElements" << endl;
	}
	else {
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
			for (vector<int>::const_iterator iter = m_wrongID.begin(); iter != m_wrongID.end(); iter++) {
				if (iter != m_wrongID.begin())
					outFile << ", ";
				outFile << *iter;
			}
			outFile << endl;
		}
		if (!m_nonIntID.empty()) {
			outFile << "Puzzle of size cannot have the following non integer IDs: ";
			for (vector<string>::const_iterator iter = m_nonIntID.begin(); iter != m_nonIntID.end(); iter++) {
				if (iter != m_nonIntID.begin())
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
		//TODO: need to report missing corners
		if (m_wrongNumberOfStraightEdges && m_wrongID.empty() && m_nonIntID.empty()
			&& m_wrongLineID.empty()) {
			outFile << "Cannot solve puzzle: wrong number of straight edges" << endl;
		}
		if (!rotation) {
			for (string corner : m_missingCorners) {
				outFile << "Cannot solve puzzle: missing corner element " << corner << endl;
			}
		}
		else {
			if (m_missingCorners.size() > 0) {
				outFile << "Cannot solve puzzle: only " << 4 - m_missingCorners.size() << " corners available"<< endl;
			}
		}
		if (m_wrongSumOfEdges && m_wrongID.empty() && m_nonIntID.empty()
			&& m_wrongLineID.empty()) {
			outFile << "Cannot solve puzzle: sum of edges is not zero" << endl;
		}
		outFile.close();
	}
}