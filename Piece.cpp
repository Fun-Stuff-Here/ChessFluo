#include "Piece.h"

using namespace ChessModel;


Piece::Piece(Position& position, std::string& color, std::shared_ptr<Board> board)
	:position_{position},color_{color},board_{board}
{}


Position Piece::getPosition() const
{
	return position_;
}

std::string Piece::getColor() const
{
	return color_;
}


bool Piece::isOutofBound(Position position)
{
	bool isOutOfBound = position.first > topLimit;
	isOutOfBound |= position.first < bottomLimit;
	isOutOfBound |= position.second > topLimit;
	isOutOfBound |= position.second < bottomLimit;
	return isOutOfBound;
}