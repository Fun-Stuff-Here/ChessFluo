#include "King.h"

using namespace ChessModel;

King::King(Position& position, std::string& color, std::shared_ptr<Board> board)
	:Piece(position, color,board)
{}

std::vector<Position> King::getMoves() const
{
	std::vector<Position> positions;
	
	//https://codereview.stackexchange.com/questions/53875/generating-possible-chess-moves
	Position offsets[] = {
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
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
		if (!isOutofBound(possiblePosition))
			positions.push_back(possiblePosition);
	}
	return positions;
}