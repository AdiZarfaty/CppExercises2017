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
	friend class Board;
	const int m_numberOfPieces;
	int m_sumOfEdges;
	int m_numOfStraightEdges_rl;
	int m_numOfStraightEdges_tb;
	bool error;
	bool cornerTL;
	bool cornerTR;
	bool cornerBL;
	bool cornerBR;
	vector<int> missingID;
	vector<int> wrongID;
	vector<int> wrongLineID;
	vector<string> wrongLineString;
public:
	BoardErrors(int);
	~BoardErrors();
	bool hasErrors() const;
	void printErrors(string) const;
	void sortErrors();
};

