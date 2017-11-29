
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

	list<Piece*>::iterator iter = optionsList.begin();

	int pieceTryiesCounter = 0; // for debug

	while (iter != optionsList.end()){
		Piece* tilePtr = *iter; // take the tile

		if (i == (m_heigt - 1)) // Last Row
		{
			if (tilePtr->getBottom() != 0)
			{
				// tile mismatch at bottom
				pieceTryiesCounter++;
				iter++;
				continue;
			}
		}

		if (j == (m_width - 1))
		{
			if (tilePtr->getRight() != 0)
			{
				// tile mismatch at right
				pieceTryiesCounter++;
				iter++;
				continue;
			}
		}

		// avoid trying a similar piece to one we tried before
		list<Piece*>::iterator iterTriedBefore = optionsList.begin();
		bool triedThisPieceTypeBefore = false;

		int optionListLength = (int)optionsList.size();

		while (iterTriedBefore != iter) {
			if (((*iter)->getBottom() == (*iterTriedBefore)->getBottom())
				&& ((*iter)->getRight() == (*iterTriedBefore)->getRight()))
			{
				//we tried this "type" of piece before and it did not work
				triedThisPieceTypeBefore = true;
				break;
			}
			else
			{
				iterTriedBefore++;
			}
		}

		if (triedThisPieceTypeBefore)
		{
			pieceTryiesCounter++;
			iter++;
			continue;
		}

		internalAccessPiecePtr(i, j) = tilePtr; // place the tile in the location


		// for debug
		//if ((m_heigt*m_width) - (i*m_width + j) > 25)
		//{
		//	system("CLS");
		//	std::cout << debugGetSolutionAsString(i, j, pieceTryiesCounter, optionListLength) << endl << std::flush;
		//}

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
			pieceTryiesCounter++;
		}
	}

	return false; // tried all options, no solution for i,j
}

string Solution::debugGetSolutionAsString(int posi, int posj, int pieceTryiesCounter, int optionListLength)
{
	if (posi == 0 && pieceTryiesCounter==0) //first run
	{
		m_triedSolutionCounter.resize(m_heigt);
		m_optionsCounter.resize(m_heigt);
	}

	if (posj == 0 && pieceTryiesCounter == 0) //first run
	{
		m_triedSolutionCounter.at(posi).resize(m_width);
		m_optionsCounter.at(posi).resize(m_width);
	}

	m_triedSolutionCounter.at(posi).at(posj) = pieceTryiesCounter;
	m_optionsCounter.at(posi).at(posj) = optionListLength;


	std::stringstream output;
	output << "trying (" << m_heigt << " x " << m_width << ") board" << endl; //debug !
	output << "pos:("<< posi <<","<< posj << ") trying piece " << pieceTryiesCounter+1 << " out of " << optionListLength << endl; //debug !

	for (int i = 0; i < m_heigt; i++)
	{
		for (int j = 0; j < m_width; j++) {
			if (j > 0) {
				output << "|";
			}

			//const Piece* piecePtr = internalGetPiecePtr(i, j);
			//int id;
			//if (piecePtr != nullptr)
			//{
			//	id = piecePtr->getId();
			//}
			//else
			//{
			//	id = 0;
			//}
			//
			//if (id < 10)
			//{
			//	// space for single digits
			//	output << " ";
			//}
			
			int perc;
			if ((i*m_width + j) <= (posi*m_width +posj))
			{
				perc = (int) trunc(100*m_triedSolutionCounter.at(i).at(j) / (float)m_optionsCounter.at(i).at(j));
			}
			else
			{
				perc = 100;
			}
			if (perc < 10)
			{
				// space for single digits
				output << " ";
			}
			if (perc < 100)
			{
				// space for double digits
				output << " ";
			}

			output /*<< std::to_string(id) << ":" */ << perc << "%";
		}

		output << std::endl;
	}

	return output.str();
}
