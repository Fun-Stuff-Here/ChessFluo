#include "Board.h"
#include <algorithm>

using namespace ChessModel;

Board::Board()
{

	std::string colorPlayer1 = "bluelaite";
	std::string colorPlayer2 ="vertmoisi";
	
	Position bishopleft1{ 3,1 },
		bishopright1{ 6,1 },
		bishopleft2{ 3,8 },
		bishopright2{ 6,8 },
		positionLeftKnight1{ 2, 1 },
		positionRightKnight1{ 7, 1 },
		positionLeftKnight2{ 2, 8 },
		positionRightKnight2{ 7, 8 },
		positionKing1{ 4,1 },
		positionKing2{ 4,8 };


	PiecePtr bishopLeft1(new Bishop{ bishopleft1,colorPlayer1,this }),
		bishopRight1(new Bishop{ bishopright1,colorPlayer1,this }),
		bishopLeft2(new Bishop{ bishopleft2,colorPlayer2,this }),
		bishopRight2(new Bishop{ bishopright2,colorPlayer2,this }),
		knightLeft1(new Knight{ positionLeftKnight1, colorPlayer1, this }),
		knightRight1(new Knight{ positionRightKnight1, colorPlayer1, this }),
		knightLeft2(new Knight{ positionLeftKnight2, colorPlayer2, this }),
		knightRight2(new Knight{ positionRightKnight2, colorPlayer2, this }),
		king1(new King{ positionKing1, colorPlayer1,this }),
		king2(new King{ positionKing2,colorPlayer2,this });

	pieces_.insert({ bishopLeft1->getPosition(),bishopLeft1 });
	pieces_.insert({ bishopRight1->getPosition(),bishopRight1 });
	pieces_.insert({ bishopLeft2->getPosition(),bishopLeft2 });
	pieces_.insert({ bishopRight2->getPosition(),bishopRight2 });
	pieces_.insert({ knightLeft1->getPosition(),knightLeft1 });
	pieces_.insert({ knightRight1->getPosition(),knightRight1 });
	pieces_.insert({ knightLeft2->getPosition(),knightLeft2 });
	pieces_.insert({ knightRight2->getPosition(),knightRight2 });
	pieces_.insert({ king1->getPosition(),king1 });
	pieces_.insert({ king2->getPosition(),king2 });

}

PiecePtr Board::move(PiecePtr& piece, Position& position)
{
	
	auto moves = piece->getMoves();
	auto it = std::find_if(moves.begin(), moves.end(), [&position](Position possiblePosition)->bool {return possiblePosition == position; });
	
	if (it == moves.end())
		throw impossibleMove();
	
	PiecePtr pieceEaten = getPiece(position);

	if (pieceEaten!=nullptr)
		pieces_.erase(position);

	pieces_.erase(piece->getPosition());
	piece->setPosition(position);
	pieces_.insert({ position, piece });

	return pieceEaten;
}

PiecePtr Board::move(PiecePtr& piece, Position&& position)
{
	return move(piece,position);
}

mapPieces Board::getPieces()
{
	return pieces_;
}

PiecePtr Board::getPiece(Position& position)
{
	PiecePtr piece = nullptr;
	try
	{
		piece = pieces_.at(position);
	}
	catch (const std::out_of_range&)
	{
		piece = nullptr;
	}

		return piece;
}

PiecePtr Board::getPiece(Position&& position)
{
	return getPiece(position);
}

bool Board::isUnoccupied(Position& position)
{
	return getPiece(position)==nullptr;
}

bool Board::isOccupiedByOtherColor(Position& position, std::string color)
{
	if (!isUnoccupied(position))
	{
		PiecePtr piece = getPiece(position);
		return (piece->getColor() != color);
	}
	return false;
}

void Board::addPiece(PiecePtr& pieceToAdd)
{
	pieces_.insert({ pieceToAdd->getPosition(), pieceToAdd});
}