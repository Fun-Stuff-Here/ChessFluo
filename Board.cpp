#include "Board.h"

using namespace ChessModel;

Board::Board()
{
	auto board = std::make_shared<Board>(this);

	std::string colorPlayer1 = "bluelaite";
	std::string colorPlayer2 ="vertmoisi";
	
	Position bishopleft1{ 3,1 },
		bishopright1{ 6,1 },
		bishopleft2{ 3,8 },
		bishopright2{ 6,8 };


	Bishop left1{ bishopleft1,colorPlayer1,board },
		right1{ bishopright1,colorPlayer1,board },
		left2{ bishopleft2,colorPlayer2,board },
		right2{ bishopright2,colorPlayer2,board };


	Position posLeftKnight1 = { 2, 1 },
		posRightKnight1 = { 7, 1 },
		 posLeftKnight2 = { 2, 8 },
		posRightKnight2 = { 7, 8 };

	Knight leftKnight1{ posLeftKnight1, colorPlayer1, board },
		rightKnight1{ posRightKnight1, colorPlayer1, board },
		leftKnight12{ posLeftKnight2, colorPlayer1, board},
		rightKnight2{ posRightKnight2, colorPlayer1, board };

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
