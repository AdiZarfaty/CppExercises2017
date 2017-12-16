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
class BoardErrors
{
	int m_numberOfPieces = 0;
	bool m_error = false;
	bool m_firstLineIsInWrongFormat = false;
	bool m_wrongSumOfEdges = false;
	bool m_couldNotExtractNumElements = false;
	bool m_fourCorners;
	bool m_twoCorners;
	bool m_wrongNumberOfStraightEdges = false;
	vector<int> m_missingID;
	vector<int> m_wrongID; // ids that are not matching the m_numberOfPieces
	vector<string> m_nonIntID;
	vector<int> m_wrongLineID; // ids with error
	vector<string> m_wrongLineString; // ids with error - original input line
	vector<string> m_missingCorners = { "TL", "TR", "BL", "BR" }; //missing corners vector //TODO: add api, and report it in output

public:
	bool hasErrors() const;
	void checkCorners();
	void printErrors(ofstream& outFile, bool rotation) const;
	void sortMissingIDErrors();
	void setNumberOfPieces(int num)
	{
		m_numberOfPieces = num;
	}

	vector<string>& getMissingCorners() {
		return m_missingCorners;
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

	void setFourCorners()
	{
		m_fourCorners = true;
	}

	bool getFourCorners()
	{
		return m_fourCorners;
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
	void addNonIntID(string id)
	{
		m_nonIntID.push_back(id);
		m_error = true;
	}
	void addWrongLine(int id, string line)
	{
		m_wrongLineID.push_back(id);
		m_wrongLineString.push_back(line);
		m_error = true;
	}
	void setTwoCorners()
	{
		m_twoCorners = true;
	}
	bool getTwoCorners()
	{
		return m_twoCorners;
	}
};

