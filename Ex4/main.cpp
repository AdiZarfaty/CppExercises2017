#include "ex4headers.h"

using namespace std;

void example1() {
	list<Puzzle2dPiece<5>> pieces = {{0, 3, 2, -5}, {0, -2, 2, -5}};
	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	// note that there is no & on the auto below (was in previous version)
	auto some_pieces = groups.get({0, std::numeric_limits<int>::min(), 2, -5});
	for(auto piece_ptr : some_pieces) {
		std::cout << *piece_ptr << std::endl; // will print both pieces!
	}
}


void example2() {
	list<Puzzle3dPiece<1>> pieces = {{0, 1, 1, 1, -1, -1}, {0, -1, 1, 1, 1, 1}};
	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	// note that there is no & on the auto below (was in previous version)
	auto some_pieces = groups.get({0, 1, 1, 1, 1, 1});
	for(auto piece_ptr : some_pieces) {
		std::cout << *piece_ptr << std::endl; // will print nothing!
	}
}


void example3() {
	auto joker = std::numeric_limits<int>::min();
	list<Puzzle3dPiece<1>> pieces = {{0, 1, 1, 1, -1, -1}, {0, -1, 1, 1, 1, 1}};
	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	auto some_pieces = groups.get({0, joker, 1, 1, joker, joker});
	for(auto piece_ptr : some_pieces) {
		std::cout << *piece_ptr << std::endl; // will print two pieces!
	}
}


void example4() {
	vector<Puzzle2dPiece<5>> pieces = {{0, 3, 2, -5}, {0, -2, 2, -5}};
	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	auto some_pieces = groups.get({0, 3, 2, std::numeric_limits<int>::min()});
	for(auto piece_ptr : some_pieces) {
		std::cout << *piece_ptr << std::endl; // will print the first piece!
	}
}

int main() {
	cout << "example 1: will print both pieces" << endl;
	example1();

	cout << "example 2: will print nothing" << endl;
	example2();

	cout << "example 3: will print two pieces" << endl;
	example3();

	cout << "example 4: will print the first piece" << endl;
	example4();
}
