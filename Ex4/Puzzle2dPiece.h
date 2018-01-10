//
// Created by Tomer Amir on 10/01/2018.
//

#ifndef EX4_PUZZLE2DPIECE_H
#define EX4_PUZZLE2DPIECE_H

#include "Piece.h"

template <int K>
class Puzzle2dPiece: public Piece<4, K> {
public:
	Puzzle2dPiece(int l, int t, int r, int b): Piece<4, K>(l, t, r, b) {}
};


#endif //EX4_PUZZLE2DPIECE_H
