/*
* Implémentation de la Classe Pawn, Projet-INF1015
*\file		Pawn.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/

#include "Pawn.h"

using namespace ChessModel;


Pawn::Pawn(Position& position, std::string& color, Board* board) :
	Piece(position, color, board)
{}


std::vector<Position> Pawn::getMoves() const
{
	std::vector<Position> positions;

	signed int direction = color_ == COLORPLAYER1 ? 1 : -1;

	Position offset{0,direction};



	Position possiblePosition = position_;
	possiblePosition.first += offset.first;
	possiblePosition.second += offset.second;

	if (!isOutofBound(possiblePosition) && board_->isUnoccupied(possiblePosition))
		positions.push_back(possiblePosition);

	if ((position_.second == 2 || position_.second == NROWS - 1)&&positions.size()>0)
	{
		possiblePosition.first += offset.first;
		possiblePosition.second += offset.second;
		if (!isOutofBound(possiblePosition) && board_->isUnoccupied(possiblePosition))
			positions.push_back(possiblePosition);
	}


	std::vector<Position> eatingOffsets = {
		{1,direction},
		{-1,direction}
	};
	for (auto&& offset : eatingOffsets)
	{
		possiblePosition = position_;
		possiblePosition.first += offset.first;
		possiblePosition.second += offset.second;
		if (!isOutofBound(possiblePosition) && board_->isOccupiedByOtherColor(possiblePosition,color_))
			positions.push_back(possiblePosition);
	}




	return positions;
}