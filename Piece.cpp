/*
* Implémentation de la Classe Piece, Projet-INF1015
*\file		Piece.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#include "Piece.h"
#include "Board.h"
#include "exeptions.h"

using namespace ChessModel;


Piece::Piece(Position& position, std::string& color, Board* board)
	:position_{position},color_{color},board_{board}
{}

Position Piece::getPosition() const
{
	return position_;
}

void Piece::setPosition(Position& position)
{
	position_ = position;
}

void Piece::setPosition(const Position& position)
{
	position_ = position;
}

std::string Piece::getColor() const
{
	return color_;
}


bool Piece::isOutofBound(Position& position) const
{
	bool isOutOfBound = position.first > topLimit;
	isOutOfBound |= position.first < bottomLimit;
	isOutOfBound |= position.second > topLimit;
	isOutOfBound |= position.second < bottomLimit;
	//isOutOfBound |= !board_->isUnoccupied(position);
	return isOutOfBound;
}


void Piece::checkFilter(std::vector<Position>& positions)
{
	throw NotImplemented();
}