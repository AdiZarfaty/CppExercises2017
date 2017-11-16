#include "stdafx.h"
#include "Solution.h"


bool Solution::solve()
{
	return solve(0, 0);
}

bool Solution::solve(int i, int j)
{
	if (i == m_heigt)
	{
		// all the rows are solved
		return true;
	}

	list<Piece*>* optionsList = nullptr;

	if (i == 0) // First row
	{
		if (j == 0) {
			// Solve a TL corner
		} 
		else if (j == (m_width - 1)) {
			// Solve a TR corner
		}
		else
		{
			// Solve a T border
		}
	}
	else if (i == (m_heigt - 1)) // Last Row
	{
		if (j == 0) {
			//Solve a BL corner
		}
		else if (j == (m_width - 1)) {
			//Solve a BR corner
		}
		else
		{
			//Solve a B border
		}
	}
	else if (j == 0)
	{
		//Solve a L border
	}
	else if (j == (m_width - 1))
	{
		//Solve a R border
	}
	else
	{
		//Solve a middle piece
	}


	//TODO: For now - use the naive solution , todo - use real algorithm with borders and EQ classes
	optionsList = &m_remainingPieces;

	bool success = false;
	Piece* nextTile = nullptr;
	int nextj = (j + 1) % m_width; // at m_width go back to 0
	int nexti = i + ((j + 1) / m_width);

	list<Piece*>::iterator iter = optionsList->begin();

	while (iter != optionsList->end()){
		Piece* tile = *iter; // take the tile
		internalGetPiece(i, j) = tile; // place the tile in the location
		
		iter = optionsList->erase(iter); //remove from the options list, as it is no longer available
										 //TODO:FIX BUG !! - what if my tile is a square, it fits many EQ classes. when used need to remove all of them! and then need to add to all of them back in the right places!
		                                 // solutions ? keep a list of used ids, pass in the recursion a DS of available tiles
		success = solve(nexti, nextj);
		if (success)
		{
			// Solved everything
			return true;
		}
		else
		{
			// mark as unsolved (avoid garbage)
			internalGetPiece(i, j) = nullptr;
			// return this tile, and try the next option
			optionsList->insert(iter, tile);
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

			int id = internalGetPiece(i, j)->getId;
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
