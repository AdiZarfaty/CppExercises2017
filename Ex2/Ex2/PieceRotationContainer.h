#pragma once
#include"Piece.h"

// This class will hold a ptr to a piece, and a rotation of it
class PieceRotationContainer
{
	Piece* m_piecePtr;  // piecePtr is not owned by this class
	short m_rotation;  // values: 0, 1, 2, 3 (= 0, 90, 180, 270 deg)
public:
	PieceRotationContainer(): m_piecePtr(nullptr), m_rotation(0){

	}

	PieceRotationContainer(Piece* pieceptr, int rotationInDegrees) : m_piecePtr(pieceptr), m_rotation((rotationInDegrees % 360) / 90) {

	}

	PieceRotationContainer(const PieceRotationContainer& source)
	{
		m_piecePtr = source.m_piecePtr; // intentionally do a shallow copy.
		m_rotation = source.m_rotation;
	}

	Piece* GetPiece() const
	{
		return m_piecePtr;
	}

	void SetPiece(Piece* ptr)
	{
		m_piecePtr = ptr;
	}

	bool isUsed() const {
		return m_piecePtr->isUsed();
	}

	void setUsed(bool val) {
		m_piecePtr->setUsed(val);
	}

	int getId() const {
		return m_piecePtr->getId();
	}

	//get the face (with rotation)
	short getFace(int i) const {
		return m_piecePtr->getFace(((i - m_rotation + 4) % 4)); // minus rotation = clockwise rotation, +4 to avoid minus values
	}

	//get the rotation angle in degrees
	int getRotationAngle() const
	{
		return m_rotation * 90;
	}

	//get the face (with rotation)
	short getLeft() const {
		return getFace(0);
	}
	//get the face (with rotation)
	short getTop() const {
		return getFace(1);
	}
	//get the face (with rotation)
	short getRight() const {
		return getFace(2);
	}
	//get the face (with rotation)
	short getBottom() const {
		return getFace(3);
	}
};

