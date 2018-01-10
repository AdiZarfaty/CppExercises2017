//
// Created by Tomer Amir on 09/01/2018.
//

#ifndef EX4_PIECE_H
#define EX4_PIECE_H

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

template <size_t S = 4, int K = 1>
class Piece {
public:
	int sides[S];

	Piece(int first, ...)
	{
		sides[0] = first;
		va_list args;

		va_start(args, first);
		for (auto i = 1; i < S; i++) {
			sides[i] = va_arg(args, int);
		}
		va_end(args);
	}

	string getType() const {
		return to_string(sides[0]) + " " + to_string(sides[1]) + " " + to_string(sides[2]) + " " + to_string(sides[3]);
	}

	class iterator {
	private:
		Piece *piece;
		int _side = 0;
	public:
		explicit iterator(Piece *p, int side = 0): piece(p), _side(side) {}

		bool operator!=(iterator itr)
		{
			return _side != itr._side;
		}

		// prefix
		iterator operator++()
		{
			++_side;
			return *this;
		}

		int operator*() {
			return piece->sides[_side];
		}
	};

	iterator begin() {
		return iterator(this);
	}

	iterator end() {
		return iterator(this, S);
	}
};

template<typename Iterator>
auto groupPuzzlePieces(Iterator begin, Iterator end) {
	for (; begin != end; begin++) {
		auto pi = *begin;
		cout << "s ";

		for (const auto &i: pi) {
			cout << i << ", ";
		}

		cout << endl;
	}

	return "test";
}

#endif //EX4_PIECE_H
