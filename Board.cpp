#include "Board.h"

using namespace ChessModel;

Board::Board()
{
}

void Board::move(PiecePtr piece, Position position)
{
	throw NotImplemented();
}


mapPieces Board::getPieces()
{
	return pieces_;
}

PiecePtr Board::getPiece(Position position)
{
	auto it = pieces_.find(position);
	return it!=pieces_.end() ? it->second : nullptr;
}

bool Board::isUnoccupied(Position position)
{
	return getPiece(position)!=nullptr;
}
