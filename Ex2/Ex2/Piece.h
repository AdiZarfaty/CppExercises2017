#pragma once
#include <stdexcept>

class Piece {
	const int m_id;
	const short m_left; // -1 for a female edge, 0 for flat edge, 1 for male edge
	const short m_top;
	const short m_right;
	const short m_bottom;
public:
	Piece(int id, short left, short top, short right, short bottom):
		m_id(id), m_left(left), m_top(top), m_right(right), m_bottom(bottom){
	}

	int getId() const {
		return m_id;
	}
	short getTop() const {
		return m_top;
	}
	short getBottom() const {
		return m_bottom;
	}
	short getRight() const {
		return m_right;
	}
	short getLeft() const {
		return m_left;
	}

	short getFace(int i) const;
};
