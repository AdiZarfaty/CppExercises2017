#pragma once
class Piece {
	const int m_id;
	const short m_left; // -1 for a female edge, 0 for flat edge, 1 for male edge
	const short m_top;
	const short m_right;
	const short m_bottom;
	bool m_used;
public:
	Piece(int id, short left, short top, short right, short bottom):
		m_id(id), m_left(left), m_top(top), m_right(right), m_bottom(bottom){
		m_used = false;
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
	void setUsed() {
		m_used = true;
	}
	void setUnused() {
		m_used = false;
	}
	bool getUsed() {
		return m_used;
	}

	short getFace(int i) const //TODO: maybe this can replace all get_ ?
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
			//TODO: throw error
			return 0;
		}
	}

	bool isUsed() const{
		return m_used;
	}

	void setUsed(bool val) {
		m_used = val;
	}
};
