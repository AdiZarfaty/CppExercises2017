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
//TODO: remove friend and check error messages compliance to instructions
	friend class Board;
	int m_numberOfPieces;
	int m_sumOfEdges;
	bool error;
	bool firstLineIsInWrongFormat;
	bool couldNotExtractNumElements;
	bool cornerTL;
	bool cornerTR;
	bool cornerBL;
	bool cornerBR;
	bool m_wrongNumberOfStraightEdges;
	vector<int> missingID;
	vector<int> wrongID;
	vector<int> wrongLineID;
	vector<string> wrongLineString;
public:
	BoardErrors();
	~BoardErrors();
	bool hasErrors() const;
	void printErrors(ofstream& outFile) const;
	void sortErrors();
};

