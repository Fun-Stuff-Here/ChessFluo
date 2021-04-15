/*
* Implémentation de la Classe King, Projet-INF1015
*\file		King.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#include "King.h"

using namespace ChessModel;

King::King(Position& position, std::string& color, Board* board)
	:Piece(position, color,board)
{
	canBigCastle_ = true;
	canSmallCastle_ = true;
}

std::vector<Position> King::getMoves() const
{
	std::vector<Position> positions;
	
	//https://codereview.stackexchange.com/questions/53875/generating-possible-chess-moves
	Position offsets[] = {
		{1, 0},
		{0, 1},
		{0, -1},
		{-1, 0},
		{1, 1},
		{-1, 1},
		{-1, -1},
		{1, -1}
	};
	Position possiblePosition = { 0,0 };
	for (auto&& offset : offsets)
	{
		possiblePosition = position_;
		possiblePosition.first += offset.first;
		possiblePosition.second += offset.second;
		if (!isOutofBound(possiblePosition) && (board_->isUnoccupied(possiblePosition) || board_->isOccupiedByOtherColor(possiblePosition, color_)))
			positions.push_back(possiblePosition);
	}

	
	//castling
	if (canSmallCastle_)
	{
		if (color_ == COLORPLAYER1)
		{
			if (!(board_->isCheckable({ 6,1 }, color_)) &&
				!(board_->isCheckable({ 7,1 }, color_)) &&
				board_->isUnoccupied({ 6,1 }) &&
				board_->isUnoccupied({ 7,1 }))
				positions.emplace_back(7,1);
		}
		else
		{
			if (!board_->isCheckable({ 6,8 }, color_) &&
				!board_->isCheckable({ 7,8 }, color_) &&
				board_->isUnoccupied({ 6,8 }) &&
				board_->isUnoccupied({ 7,8 }))
				positions.emplace_back(7, 8);
		}
	}
	if (canBigCastle_)
	{
		if (color_ == COLORPLAYER1)
		{
			if (!board_->isCheckable({ 2,1 }, color_) &&
				!board_->isCheckable({ 3,1 }, color_) &&
				!board_->isCheckable({ 4,1 }, color_) &&
				board_->isUnoccupied({ 2,1 }) &&
				board_->isUnoccupied({ 3,1 }) &&
				board_->isUnoccupied({ 4,1 }))
				positions.emplace_back(3, 1);
		}
		else
		{
			if (!board_->isCheckable({ 2,8 }, color_) &&
				!board_->isCheckable({ 3,8 }, color_) &&
				!board_->isCheckable({ 4,8 }, color_) &&
				board_->isUnoccupied({ 2,8 }) &&
				board_->isUnoccupied({ 3,8 }) &&
				board_->isUnoccupied({ 4,8 }))
				positions.emplace_back(3, 8);
		}

	}
	

	return positions;
}

bool King::canSmallCastle()
{
	return canSmallCastle_;
}

bool King::canBigCastle()
{
	return canBigCastle_;
}

void King::moved()
{
	canBigCastle_ = false;
	canSmallCastle_ = false;
}

void King::smallCastlingRookMoved()
{
	canSmallCastle_ = false;
}

void King::bigCastlingRookMoved()
{
	canBigCastle_ = false;
}