/*
* Implémentation de la Classe Queen, Projet-INF1015
*\file		Queen.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/

#include "Queen.h"

using namespace ChessModel;


Queen::Queen(Position& position, std::string& color, Board* board) :
	Piece(position, color, board)
{}


std::vector<Position> Queen::getMoves() const
{
	std::vector<Position> positions;

	//https://codereview.stackexchange.com/questions/53875/generating-possible-chess-moves

	//right
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first++)
	{
		if (possiblePosition == position_)
			continue;
		if (board_->isUnoccupied(possiblePosition))
		{
			positions.push_back(possiblePosition);
		}
		if (!board_->isUnoccupied(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition, color_))
		{
			positions.push_back(possiblePosition);
			break;
		}
		if (!board_->isUnoccupied(possiblePosition))
			break;
	}

	//left
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first--)
	{
		if (possiblePosition == position_)
			continue;
		if (board_->isUnoccupied(possiblePosition))
		{
			positions.push_back(possiblePosition);
		}
		if (!board_->isUnoccupied(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition, color_))
		{
			positions.push_back(possiblePosition);
			break;
		}
		if (!board_->isUnoccupied(possiblePosition))
			break;
	}

	//up
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.second++)
	{
		if (possiblePosition == position_)
			continue;
		if (board_->isUnoccupied(possiblePosition))
		{
			positions.push_back(possiblePosition);
		}
		if (!board_->isUnoccupied(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition, color_))
		{
			positions.push_back(possiblePosition);
			break;
		}
		if (!board_->isUnoccupied(possiblePosition))
			break;
	}

	//down
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.second--)
	{
		if (possiblePosition == position_)
			continue;
		if (board_->isUnoccupied(possiblePosition))
		{
			positions.push_back(possiblePosition);
		}
		if (!board_->isUnoccupied(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition, color_))
		{
			positions.push_back(possiblePosition);
			break;
		}
		if (!board_->isUnoccupied(possiblePosition))
			break;
	}



	//top right diagonal
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first++, possiblePosition.second++)
	{
		if (possiblePosition == position_)
			continue;
		if (board_->isUnoccupied(possiblePosition))
		{
			positions.push_back(possiblePosition);
		}
		if (!board_->isUnoccupied(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition, color_))
		{
			positions.push_back(possiblePosition);
			break;
		}
		if (!board_->isUnoccupied(possiblePosition))
			break;

	}

	//top left diagonal
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first--, possiblePosition.second++)
	{
		if (possiblePosition == position_)
			continue;
		if (board_->isUnoccupied(possiblePosition))
		{
			positions.push_back(possiblePosition);
		}
		if (!board_->isUnoccupied(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition, color_))
		{
			positions.push_back(possiblePosition);
			break;
		}
		if (!board_->isUnoccupied(possiblePosition))
			break;
	}

	//buttom right diagonal
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first++, possiblePosition.second--)
	{
		if (possiblePosition == position_)
			continue;
		if (board_->isUnoccupied(possiblePosition))
		{
			positions.push_back(possiblePosition);
		}
		if (!board_->isUnoccupied(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition, color_))
		{
			positions.push_back(possiblePosition);
			break;
		}
		if (!board_->isUnoccupied(possiblePosition))
			break;
	}

	//buttom left diagonal
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first--, possiblePosition.second--)
	{
		if (possiblePosition == position_)
			continue;
		if (board_->isUnoccupied(possiblePosition))
		{
			positions.push_back(possiblePosition);
		}
		if (!board_->isUnoccupied(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition, color_))
		{
			positions.push_back(possiblePosition);
			break;
		}
		if (!board_->isUnoccupied(possiblePosition))
			break;
	}


	return positions;
}
