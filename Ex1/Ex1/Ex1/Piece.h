#pragma once
class Piece {
	int m_id;
	short m_left; // -1 for a female edge, 0 for flat edge, 1 for male edge
	short m_top;
	short m_right;
	short m_bottom;
public:
	Piece(int id, short top, short bottom, short right, short left):
		m_id(id), m_top(top), m_bottom(bottom), m_right(right), m_left(left){
	}

	int getId() {
		return m_id;
	}
	short getTop() {
		return m_top;
	}
	short getBottom() {
		return m_bottom;
	}
	short getRight() {
		return m_right;
	}
	short getLeft() {
		return m_left;
	}
};
