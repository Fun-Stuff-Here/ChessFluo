/*
* Implémentation de la Classe Bishop, Projet-INF1015
*\file		Bishop.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#include "Bishop.h"


using namespace ChessModel;


Bishop::Bishop(Position& position, std::string& color, Board* board)
	:Piece(position, color, board)
{}

std::vector<Position> Bishop::getMoves() const
{
	std::vector<Position> positions;

	//https://codereview.stackexchange.com/questions/53875/generating-possible-chess-moves

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
