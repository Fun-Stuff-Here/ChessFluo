#include "Piece.h"
#include "Board.h"

using namespace ChessModel;


Piece::Piece(Position& position, std::string& color, Board* board)
	:position_{position},color_{color},board_{board}
{}


Position Piece::getPosition() const
{
	return position_;
}

void Piece::setPosition(Position position)
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
	isOutOfBound |= !board_->isUnoccupied(position);
	return isOutOfBound;
}