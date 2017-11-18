// Ex1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

int main()
{
	//parse the first line and derive NumElements
	string first_line;
	getline(cin, first_line, '=');
	if (first_line != "NumElements") {
		cout << "first line is in a wrong format" << endl;
	}
	try {
		getline(cin, first_line);
		int numElements = stoi(first_line);
	
		//create the board and its pieces
		string line;
		int id;
		int sides[4];
		vector<int> ids(numElements);
		Board board(numElements);
		board.readBoard();

		if (board.getError().hasErrors()) {
			board.getError().printErrors();
		}
		else {
			// Solve the puzzle
		}
	}
	catch (const invalid_argument& e) {
		cout << "ERROR: could not extract number of elements" << endl;
	}

	return 0;
}

