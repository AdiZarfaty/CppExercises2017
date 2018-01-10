#include <list>
#include <iostream>
#include "Puzzle2dPiece.h"

using std::list;
using std::cout;
using std::endl;

int main() {
	std::cout << "Hello, World!" << std::endl;

	Piece<7> p(1, 2, 3, 4, 5, 6, 7);

	for (const auto &i: p) {
		cout << i << endl;
	}

	std::list<Puzzle2dPiece<5>> pieces = {{0, 3, 2, -5}, {0, -2, 2, -5}};

	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	auto somePieces = groups.get({0, std::numeric_limits<int>::min(), 2, -5});

	return 0;
}