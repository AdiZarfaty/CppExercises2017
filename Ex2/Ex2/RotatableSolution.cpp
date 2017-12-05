#include "RotatableSolution.h"


bool RotatableSolution::solve()
{
	return solve(0, 0);
}

bool RotatableSolution::solve(int i, int j)
{
	short leftFit;
	short topFit;

	if (i == 0) // First row
	{
		topFit = 0;
	}
	else
	{
		topFit = -internalGetPiecePtr(i - 1, j).GetPiece()->getBottom();
	}

	if (j == 0) // First column
	{
		leftFit = 0;
	}
	else
	{
		leftFit = -internalGetPiecePtr(i, j - 1).GetPiece()->getRight();
	}

	list<PieceRotationContainer>& optionsList = m_Pieces->getEQClass(leftFit, topFit);

	bool success = false;

	list<PieceRotationContainer>::iterator iter = optionsList.begin();

	int pieceTryiesCounter = 0; // for debug

	while (iter != optionsList.end()) {
		// go to the first unused tile
		if (iter->GetPiece()->isUsed())
		{
			iter++;
			continue;
		}

		PieceRotationContainer tilePtr = *iter; // take the tile

		if (i == (m_heigt - 1)) // Last Row
		{
			if (tilePtr.GetPiece()->getBottom() != 0)
			{
				// tile mismatch at bottom
				pieceTryiesCounter++;
				iter++;
				continue;
			}
		}

		if (j == (m_width - 1))
		{
			if (tilePtr.GetPiece()->getRight() != 0)
			{
				// tile mismatch at right
				pieceTryiesCounter++;
				iter++;
				continue;
			}
		}

		// avoid trying a similar piece to one we tried before
		list<PieceRotationContainer>::iterator iterTriedBefore = optionsList.begin();
		bool triedThisPieceTypeBefore = false;

		int optionListLength = (int)optionsList.size();

		while (iterTriedBefore != iter) {
			// go to unused tile that we tried before
			if (iterTriedBefore->GetPiece()->isUsed())
			{
				iterTriedBefore++;
				continue;
			}

			if (((iter)->getBottom() == (iterTriedBefore)->getBottom())
				&& ((iter)->getRight() == (iterTriedBefore)->getRight())) //TODO: can make PieceRotationContainer::EqualEdges
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

		tilePtr.GetPiece()->setUsed(true); // mark the piece as used
		internalAccessPiecePtr(i, j) = tilePtr; // copy the rotation container to the solution


												// for debug
												if ((m_heigt*m_width) - (i*m_width + j) > 1)
												{
													debugGetSolutionAsString(i, j, pieceTryiesCounter, optionListLength);
												}

		if ((i == (m_heigt - 1)) && (j == (m_width - 1)))
		{
			success = true;
		}
		else
		{
			int nextj = (j + 1) % m_width; // at m_width go back to 0
			int nexti = i + ((j + 1) / m_width);

			success = solve(nexti, nextj); //send by copy the current state of remaining pieces

		}
		if (success)
		{
			// Solved everything
			return true;
		}
		else
		{
			// mark as unsolved (avoid garbage)
			internalAccessPiecePtr(i, j).GetPiece()->setUsed(false); // mark the piece as unused
			iter++;
			pieceTryiesCounter++;
		}
	}

	return false; // tried all options, no solution for i,j
}

time_t global_last_debug_write_to_screen = time(NULL);

string RotatableSolution::debugGetSolutionAsString(int posi, int posj, int pieceTryiesCounter, int optionListLength)
{

	if (m_triedSolutionCounter.size() != m_heigt) //first run
	{
		m_triedSolutionCounter.resize(m_heigt);
		m_optionsCounter.resize(m_heigt);
	}

	if (m_triedSolutionCounter.at(posi).size() != m_width) //first run
	{
		m_triedSolutionCounter.at(posi).resize(m_width);
		m_optionsCounter.at(posi).resize(m_width);
	}

	m_triedSolutionCounter.at(posi).at(posj) = pieceTryiesCounter;
	m_optionsCounter.at(posi).at(posj) = optionListLength;

	time_t diff = time(NULL) - global_last_debug_write_to_screen; //time(nullptr)->tm_sec - global_last_debug_write_to_screen->tm_sec;
	if (diff < 2)
	{
		return "";
	}


	std::stringstream output;
	output << "trying (" << m_heigt << " x " << m_width << ") board" << endl; //debug !
	output << "pos:(" << posi << "," << posj << ") trying piece " << pieceTryiesCounter + 1 << " out of " << optionListLength << endl; //debug !

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
			if ((i*m_width + j) <= (posi*m_width + posj))
			{
				perc = (int)trunc(100 * m_triedSolutionCounter.at(i).at(j) / (float)m_optionsCounter.at(i).at(j));
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


	system("CLS");
	std::cout << output.str() << endl << std::flush;
	//update time of last write
	global_last_debug_write_to_screen = time(NULL);

	return output.str();
}

