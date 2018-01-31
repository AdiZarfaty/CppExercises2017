#include "ex4headers.h"

using namespace std;

//int main() {
//	std::list<Puzzle2dPiece<5>> pieces = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 1}, {-5, 0, 0, 0}, {1, 0, 0, 1}};
//	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
//	// note that there is no & on the auto below (was in previous version)
//	auto some_pieces = groups.get({std::numeric_limits<int>::min(), 0, 0, std::numeric_limits<int>::min()});
//
//	for(auto piece_ptr : some_pieces) {
//		std::cout << *piece_ptr << std::endl; // will print both pieces!
//	}
//
//	return 0;
//}

//int main() {
//	list<Puzzle3dPiece<1>> pieces = {{0, 1, 1, 1, -1, -1}, {0, -1, 1, 1, 1, 1}};
//	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
//	// note that there is no & on the auto below (was in previous version)
//	auto some_pieces = groups.get({0, 1, 1, 1, 1, 1});
//	for(auto piece_ptr : some_pieces) {
//		std::cout << *piece_ptr << std::endl; // will print nothing!
//	}
//}

int main() {
	vector<Puzzle2dPiece<5>> pieces = {{0, 3, 2, -5}, {0, -2, 2, -5}};
	auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	auto some_pieces = groups.get({0, 3, 2, std::numeric_limits<int>::min()});
	for(auto piece_ptr : some_pieces) {
		std::cout << *piece_ptr << std::endl; // will print the first piece!
	}
}

