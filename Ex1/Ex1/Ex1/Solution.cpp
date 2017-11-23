
#include "Solution.h"


bool Solution::solve()
{
	return solve(0, 0, *m_Pieces);
}

bool Solution::solve(int i, int j, PieceEQClasses remainingPieces)
{
	short leftFit;
	short topFit;

	if (i == 0) // First row
	{
		topFit = 0;
	}
	else
	{
		topFit = -internalGetPiecePtr(i - 1, j)->getBottom();
	}

	if (j == 0) // First column
	{
		leftFit = 0;
	}
	else
	{
		leftFit = -internalGetPiecePtr(i, j - 1)->getRight();
	}

	list<Piece*>& optionsList = remainingPieces.getEQClass(leftFit, topFit);

	bool success = false;
	Piece* nextTilePtr = nullptr;

	list<Piece*>::iterator iter = optionsList.begin();

	while (iter != optionsList.end()){
		Piece* tilePtr = *iter; // take the tile

		if (i == (m_heigt - 1)) // Last Row
		{
			if (tilePtr->getBottom() != 0)
			{
				// tile mismatch at bottom
				iter++;
				continue;
			}
		}

		if (j == (m_width - 1))
		{
			if (tilePtr->getRight() != 0)
			{
				// tile mismatch at right
				iter++;
				continue;
			}
		}

		internalAccessPiecePtr(i, j) = tilePtr; // place the tile in the location
		
		iter = optionsList.erase(iter); //remove from the options list, as it is no longer available
		
		if ((i == (m_heigt - 1)) && (j == (m_width - 1)))
		{
			success = true;
		}
		else
		{
			int nextj = (j + 1) % m_width; // at m_width go back to 0
			int nexti = i + ((j + 1) / m_width);

			success = solve(nexti, nextj, remainingPieces); //send by copy the current state of remaining pieces
			
		}
		if (success)
		{
			// Solved everything
			return true;
		}
		else
		{
			// mark as unsolved (avoid garbage)
			internalAccessPiecePtr(i, j) = nullptr;
			// return this tile, and try the next option
			optionsList.insert(iter, tilePtr);
			//iter++; //TODO: does iter need to be ++ or does the erase+insert moved it? needs testing
		}
	}

	return false; // tried all options, no solution for i,j
}

string Solution::debugGetSolutionAsString()
{
	std::stringstream output;
	for (int i = 0; i < m_heigt; i++)
	{
		for (int j = 0; j < m_width; j++) {
			if (j > 0) {
				output << ", ";
			}

			int id = internalGetPiecePtr(i, j)->getId();
			if (id < 10)
			{
				// space for single digits
				output << " ";
			}

			output << std::to_string(id);
		}

		output << std::endl;
	}

	return output.str();
}
