#include <list>
#include <iostream>
#include "Puzzle2dPiece.h"

int main() {
	std::list<Puzzle2dPiece<5>> pieces = {{0, 3, 2, -5}, {0, -2, 2, -5}};
	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	// note that there is no & on the auto below (was in previous version)
	auto some_pieces = groups.get({0, std::numeric_limits<int>::min(), 2, -5});

	for(auto piece_ptr : some_pieces) {
		std::cout << *piece_ptr << std::endl; // will print both pieces!
	}

	return 0;
}