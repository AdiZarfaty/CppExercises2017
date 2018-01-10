//
// Created by Tomer Amir on 10/01/2018.
//

#ifndef EX4_PUZZLE3DPIECE_H
#define EX4_PUZZLE3DPIECE_H


#include "Piece.h"

template <int K>
class Puzzle3dPiece: public Piece<6, K> {
public:
	Puzzle3dPiece(int l, int t, int r, int b, int u, int d): Piece<6, K>(l, t, r, b, u, d) {}
};


#endif //EX4_PUZZLE3DPIECE_H
