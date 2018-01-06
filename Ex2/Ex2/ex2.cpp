#include <iostream>
#include "Board.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::invalid_argument;

bool isInteger(const std::string & s)
{
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

	char * p ;
	strtol(s.c_str(), &p, 10) ;

	return (*p == 0) ;
}

int main(int argc, char *argv[])
{
	bool rotate;
	ifstream inFile;
	ofstream outFile;
	int threads = 4;

	// for debug - catch heap corruptions: _CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
	if (argc < 3) {
		cerr << "ERROR: expecting at least 2 command line arguments" << endl;
		return 0;
	}
	if (argc > 6) {
		cerr << "ERROR: expecting at most 5 command line arguments" << endl;
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

		for (int i = 1; i < argc; i++) {
			if (string(argv[i]) == "-rotate") {
				rotate = true;
			} else if (string(argv[i]) == "-threads") {
				if (i == argc - 1) {
					cerr << "ERROR: No thread number given after the -threads flag " << endl;
					return 0;
				}

				auto nextArg = string(argv[i + 1]);

				if (!isInteger(nextArg)) {
					cerr << "ERROR: Illegal thread number given: " << nextArg << endl;
					return 0;
				}

				threads = stoi(nextArg);
				i++;
			} else {
				if (infilefound)
				{
					outFile.open(argv[i]);
					if (!outFile) {
						cerr << "ERROR: Unable to open output file " << argv[2] << endl;
						return 0;
					}
					outfilefound = true;
				}
				else
				{
					inFile.open(argv[i]);
					if (!inFile) {
						cerr << "ERROR: Unable to open input file " << argv[1] << endl;
						return 0;
					}
					infilefound = true;
				}
			}
		}

		if (!infilefound || !outfilefound) {
			cerr << "ERROR: arguments provided are incorrect" << endl;
			return 0;
		}
	}

	Board board(&inFile, &outFile, rotate, threads);
	board.readBoard();
	board.solve();
	board.writeResponseToFile();
	return 0;
}

