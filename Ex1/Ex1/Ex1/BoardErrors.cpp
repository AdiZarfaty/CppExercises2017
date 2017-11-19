#include "stdafx.h"
#include "BoardErrors.h"

BoardErrors::BoardErrors()
{
	m_sumOfEdges = 0;

}

BoardErrors::~BoardErrors()
{
	missingID.clear();
	wrongID.clear();
	wrongLineID.clear();
	wrongLineString.clear();
}

bool BoardErrors::hasErrors() const
{
	return error;
}

void BoardErrors::sortErrors() {
	sort(missingID.begin(), missingID.end());
}

void BoardErrors::printErrors(string filePath) const
{
	ofstream outFile;
	outFile.open(filePath);
	if (!outFile) {
		cerr << "ERROR: Unable to open output file " << filePath << endl;
		exit(1); //check if we can use exit
	}
	if (!missingID.empty()) {
		outFile << "Missing puzzle element(s) with the following IDs: ";
		for (vector<int>::const_iterator iter = missingID.begin(); iter != missingID.end(); iter++) {
			if (iter != missingID.begin() && iter != missingID.end() - 1)
				outFile << ", ";
			outFile << *iter;
		}
		outFile << endl;
	}
	if (!wrongID.empty()) {
		outFile << "Puzzle of size " << m_numberOfPieces << " cannot have the following IDs: ";
		for (vector<int>::const_iterator iter  = wrongID.begin(); iter != wrongID.end(); iter++) {
			if (iter != wrongID.begin() && iter != wrongID.end() - 1)
				outFile << ", ";
			outFile << *iter;
		}
		outFile << endl;
	}
	if (!wrongLineID.empty()) {
		for (int i = 0; i<wrongLineID.size(); i++) {
			outFile << "Puzzle ID " << wrongLineID[i] << "has wrong data: " << wrongLineString[i];
		}
		outFile << endl;
	}
	if (m_wrongNumberOfStraightEdges)
		outFile << "Cannot solve puzzle: wrong number of straight edges" << endl;
	if(!cornerTL)
		outFile << "Cannot solve puzzle: missing corner element TL" << endl;
	if (!cornerTR)
		outFile << "Cannot solve puzzle: missing corner element TR" << endl;
	if (!cornerBL)
		outFile << "Cannot solve puzzle: missing corner element BL" << endl;
	if (!cornerBR)
		outFile << "Cannot solve puzzle: missing corner element BR" << endl;
	if(m_sumOfEdges != 0)
		outFile << "Cannot solve puzzle: sum of edges is not zero" << endl;
	outFile.close();
}