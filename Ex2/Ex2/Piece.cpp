#include "Piece.h"
short Piece::getFace(int i) const
{
	switch (i) {
	case 0:
		return getLeft();
	case 1:
		return getTop();
	case 2:
		return getRight();
	case 3:
		return getBottom();
	default:
		throw std::runtime_error("invalid face");
		return 0;
	}
}

