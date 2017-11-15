using namesapce std;

class Piece {
	int id, left, top, right, bottom;
public:
	Piece(int, int, int, int, int);

	int getId() {
		return id;
	}
	int getTop() {
		return top;
	}
	int getBottom() {
		return bottom;
	}
	int getRight() {
		return right;
	}
	int getLeft() {
		return left;
	}
};

Piece::Piece(int id, int left, int top, int right, int bottom) {
	this.id = id;
	this.top = top;
	this.bottom = bottom;
	this.right = right;
	this.left = left;
}