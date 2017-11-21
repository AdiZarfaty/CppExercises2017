#pragma once
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <algorithm>

using std::vector;
using std::string;
using std::cerr;
using std::endl;
using std::iterator;
using std::sort;
using std::ofstream;
//TODO: treat duplicate as wrongLine
class BoardErrors
{
	int m_numberOfPieces = 0;
	int m_sumOfEdges = 0; //TODO: move to board
	bool m_error = false;
	bool m_firstLineIsInWrongFormat = false;
	bool m_wrongSumOfEdges = false;
	bool m_couldNotExtractNumElements = false;
	bool m_cornerTLexist = false;
	bool m_cornerTRexist = false;
	bool m_cornerBLexist = false;
	bool m_cornerBRexist = false;
	bool m_wrongNumberOfStraightEdges = false;
	vector<int> m_missingID;
	vector<int> m_wrongID; // ids that are not matching the m_numberOfPieces //TODO: change to string 
	vector<int> m_wrongLineID; // ids with error
	vector<string> m_wrongLineString; // ids with error - original input line

public:
	bool hasErrors() const;
	bool checkCorners();
	void printErrors(ofstream& outFile) const;
	void sortErrors();
	void setNumberOfPieces(int num)
	{
		m_numberOfPieces = num;
	}

	int& sumOfEdges()
	{
		return m_sumOfEdges;
	}

	void setWrongSumOfEdges() {
		m_wrongSumOfEdges = true;
		m_error = true;
	}

	void setFirstLineIsInWrongFormat()
	{
		m_firstLineIsInWrongFormat = true;
		m_error = true;
	}

	void setCouldNotExtractNumElements()
	{
		m_couldNotExtractNumElements = true;
		m_error = true;
	}

	void setCornerTLexist()
	{
		m_cornerTLexist = true;
	}

	void setCornerTRexist()
	{
		m_cornerTRexist = true;
	}

	void setCornerBLexist()
	{
		m_cornerBLexist = true;
	}

	void setCornerBRexist()
	{
		m_cornerBRexist = true;
	}

	void setWrongNumberOfStraightEdges()
	{
		m_wrongNumberOfStraightEdges = true;
		m_error = true;
	}

	void addMissingID(int id)
	{
		m_missingID.push_back(id);
		m_error = true;
	}
	void addWrongID(int id)
	{
		m_wrongID.push_back(id);
		m_error = true;
	}
	void addWrongLine(int id, string line)
	{
		m_wrongLineID.push_back(id);
		m_wrongLineString.push_back(line);
		m_error = true;
	}

	void addDuplicateID(int id)
	{
		m_duplicateID.push_back(id);
		m_error = true;
	}

};

