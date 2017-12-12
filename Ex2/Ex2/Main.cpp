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
	bool rotate;
	ifstream inFile;
	ofstream outFile;
	// debug - catch heap corruptions: _CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
	if (argc > 4) {
		cerr << "ERROR: expecting at most 3 command line arguments" << endl;
			return 0;
	}
	if (argc == 3) {
		rotate = false;
		inFile.open(argv[1]);
		if (!inFile) {
			cerr << "ERROR: Unable to open input file " << argv[1] << endl;
			return 0;
		}
		outFile.open(argv[2]);
		if (!outFile) {
			cerr << "ERROR: Unable to open output file " << argv[2] << endl;
			return 0;
		}
	}
	else {
		bool infilefound = false;
		bool outfilefound = false;
		for (int i = 1; i < 4; i++) {
			if (argv[i] != "-rotate") {
				if (infilefound)
				{
					outFile.open(argv[2]);
					if (!outFile) {
						cerr << "ERROR: Unable to open output file " << argv[2] << endl;
						return 0;
					}
					outfilefound = true;
				}
				else
				{
					inFile.open(argv[1]);
					if (!inFile) {
						cerr << "ERROR: Unable to open input file " << argv[1] << endl;
						return 0;
					}
					infilefound = true;
				}
			}
			else {
				rotate = true;
			}
		}
		if (!infilefound || !outfilefound || !rotate) {
			cerr << "ERROR: arguments provided are incorrect" << endl;
			return 0;
		}
	}
	Board board = Board(&inFile, &outFile, rotate);
	board.readBoard();
	board.solve();
	board.writeResponseToFile();
	return 0;
}

