#include "Knight.h"

using namespace ChessModel;

Knight::Knight(Position& position, std::string& color, std::shared_ptr<Board> board)
	:Piece(position, color,board)
{}


std::vector<Position> Knight::getMoves() const
{
	std::vector<Position> positions;

	//https://codereview.stackexchange.com/questions/53875/generating-possible-chess-moves
	Position offsets[] = {
        {-2, 1},
        {-1, 2},
        {1, 2},
        {2, 1},
        {2, -1},
        {1, -2},
        {-1, -2},
        {-2, -1}
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