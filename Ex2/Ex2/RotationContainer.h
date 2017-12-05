#include "Piece.h"
class RotationContainer
{
	Piece *piece;
	int rotation;
public:
	RotationContainer(Piece *piece, int rotation) : piece(piece), rotation(rotation) {};
	~RotationContainer() {
		delete piece;
	}
	Piece * getPiece() {
		return piece;
	}
	int getRotation() {
		return rotation;
	}
};

