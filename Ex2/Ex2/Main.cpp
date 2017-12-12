// Ex1.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <iterator>
#include<string>
#include <stdexcept>
#include "Board.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::invalid_argument;

int main(int argc, char *argv[])
{
	// debug - catch heap corruptions: _CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
	if (argc != 3) {
		cerr << "ERROR: expecting 2 command line arguments" << endl;
			return 0;
	}
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile) {
		cerr << "ERROR: Unable to open input file " << argv[1] << endl;
		return 0;
	}
	ofstream outFile;
	outFile.open(argv[2]);
	if (!outFile) {
		cerr << "ERROR: Unable to open output file " << argv[2] << endl;
		return 0;
	}

	Board board = Board(&inFile, &outFile, true);
	board.readBoard();
	board.solve();
	board.writeResponseToFile();
	return 0;
}

