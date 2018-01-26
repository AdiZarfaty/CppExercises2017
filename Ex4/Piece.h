//
// Created by Tomer Amir on 09/01/2018.
//

#ifndef EX4_PIECE_H
#define EX4_PIECE_H

#include <string>
#include <ostream>
#include <iostream>
#include "TypesMap.h"
#include <stdarg.h>

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::to_string;

template <int S = 4, int K = 1>
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

	string getType() {
		string res = "";

		for (int i = 0; i < S; i++) {
			res += to_string(sides[i]);

			if (i < S - 1) {
				res += ", ";
			}
		}

		return res;
	}

	int getRange() {
		return K;
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

		int& operator*() {
			return piece->sides[_side];
		}
	};

	iterator begin() {
		return iterator(this);
	}

	iterator end() {
		return iterator(this, S);
	}

	friend ostream &operator<<(ostream & os, Piece<S, K> p) {
		os << "{" << p.getType() << "}";

		return os;
	}
};

template<class T>
auto groupPuzzlePieces(T begin, T end) {
	TypesMap<typename T::value_type> m;

	for (; begin != end; begin++) {
		m.addPiece(&(*begin));
	}

	return m;
}

#endif //EX4_PIECE_H
