#include "Bishop.h"


using namespace ChessModel;


Bishop::Bishop(Position& position, std::string& color, Board* board)
	:Piece(position, color,board)
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
		positions.push_back(possiblePosition);
	}

	//top left diagonal
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first--, possiblePosition.second++)
	{
		if (possiblePosition == position_)
			continue;
		positions.push_back(possiblePosition);
	}

	//buttom right diagonal
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first++, possiblePosition.second--)
	{
		if (possiblePosition == position_)
			continue;
		positions.push_back(possiblePosition);
	}

	//buttom left diagonal
	for (Position possiblePosition = position_; (!isOutofBound(possiblePosition) || possiblePosition == position_); possiblePosition.first--, possiblePosition.second--)
	{
		if (possiblePosition == position_)
			continue;
		positions.push_back(possiblePosition);
	}

	return positions;
}