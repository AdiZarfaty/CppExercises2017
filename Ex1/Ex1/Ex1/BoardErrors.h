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
	int m_numberOfPieces = 0;
	int m_sumOfEdges = 0;
	bool m_error = false;
	bool m_firstLineIsInWrongFormat = false;
	bool m_couldNotExtractNumElements = false;
	bool m_cornerTLexist = false; //TODO: these was never filled in readboard!
	bool m_cornerTRexist = false;
	bool m_cornerBLexist = false;
	bool m_cornerBRexist = false;
	bool m_wrongNumberOfStraightEdges = false;
	vector<int> m_missingID; //TODO: never filled !
	vector<int> m_wrongID; //TODO: what is wrong id ?
	vector<int> m_wrongLineID; //TODO: what is ?
	vector<string> m_wrongLineString; //TODO: what is ?

public:
	bool hasErrors() const;
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

	void setFirstLineIsInWrongFormat()
	{
		m_firstLineIsInWrongFormat = true;
		m_error = true;
	}

	void setCouldNotExtractNumElements() //TODO: is this in the ex1 guide ?
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
	void addWrongLineID(int id)
	{
		m_wrongLineID.push_back(id);
		m_error = true;
	}
	void addWrongLineString(string s)
	{
		m_wrongLineString.push_back(s);
		m_error = true;
	}

};

