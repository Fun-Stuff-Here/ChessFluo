/*
* Implémentation de la Classe Board, Projet-INF1015
*\file		Board.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#include "Board.h"
#include <algorithm>
#include <iostream>
#include "exeptions.h"
#include "Piece.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"

using namespace ChessModel;

Board::Board()
{

	std::string colorPlayer1 = COLORPLAYER1;
	std::string colorPlayer2 = COLORPLAYER2;
	
	Position bishopleft1Position{ 3,1 },
		bishopright1Position{ 6,1 },
		bishopleft2Position{ 3,8 },
		bishopright2Position{ 6,8 },
		positionLeftKnight1Position{ 2, 1 },
		positionRightKnight1Position{ 7, 1 },
		positionLeftKnight2Position{ 2, 8 },
		positionRightKnight2Position{ 7, 8 },
		positionKing1Position{ 5,1 },
		positionKing2Position{ 5,8 },
		positionRookLeft1{1,1},
		positionRookRight1{8,1},
		positionRookLeft2{1,8},
		positionRookRight2{8,8},
		positionQueen1{4,1},
		positionQueen2{4,8};


	PiecePtr bishopleft1(new Bishop{ bishopleft1Position,colorPlayer1,this }),
		bishopRight1(new Bishop{ bishopright1Position,colorPlayer1,this }),
		bishopLeft2(new Bishop{ bishopleft2Position,colorPlayer2,this }),
		bishopRight2(new Bishop{ bishopright2Position,colorPlayer2,this }),
		knightLeft1(new Knight{ positionLeftKnight1Position, colorPlayer1, this }),
		knightRight1(new Knight{ positionRightKnight1Position, colorPlayer1, this }),
		knightLeft2(new Knight{ positionLeftKnight2Position, colorPlayer2, this }),
		knightRight2(new Knight{ positionRightKnight2Position, colorPlayer2, this }),
		king1(new King{ positionKing1Position, colorPlayer1,this }),
		king2(new King{ positionKing2Position,colorPlayer2,this }),
		rookLeft1(new Rook{positionRookLeft1,colorPlayer1,this}),
		rookRight1(new Rook{ positionRookRight1,colorPlayer1,this }),
		rookLeft2(new Rook{ positionRookLeft2,colorPlayer2,this }),
		rookRight2(new Rook{ positionRookRight2,colorPlayer2,this }),
		queen1(new Queen{positionQueen1,colorPlayer1,this}),
		queen2(new Queen{positionQueen2,colorPlayer2,this});

	addPieces(
		{
			bishopleft1,
			bishopRight1,
			bishopLeft2,
			bishopRight2,
			knightLeft1,
			knightRight1,
			knightLeft2,
			knightRight2,
			king1,
			king2,
			rookLeft1,
			rookRight1,
			rookLeft2,
			rookRight2,
			queen1,
			queen2
		}
		);

		//pawn player1
		for(size_t i = 1; i <= NCOLUMNS; i++)
		{
			Position position{i,2};
			PiecePtr pawn(new Pawn{ position , colorPlayer1,this });
			addPiece(pawn);
		}
		//pawn player2
		for (size_t i = 1; i <= NCOLUMNS; i++)
		{
			Position position{ i,7 };
			PiecePtr pawn(new Pawn{ position , colorPlayer2,this });
			addPiece(pawn);
		}

		kingColor1_ = dynamic_cast<King*>(king1.get());
		kingColor2_ = dynamic_cast<King*>(king2.get());

}

Board::Board(Empty)
{
}

Board::Board(KingOnly)
{
	std::string colorPlayer1 = COLORPLAYER1;
	std::string colorPlayer2 = COLORPLAYER2;

	Position positionKing1{ 4,1 },
		positionKing2{ 4,8 };

	PiecePtr king1(new King{ positionKing1, colorPlayer1,this }),
		king2(new King{ positionKing2,colorPlayer2,this });

	addPieces(
		{
			king1,
			king2
		}
	);
	kingColor1_ = dynamic_cast<King*>(king1.get());
	kingColor2_ = dynamic_cast<King*>(king2.get());
}



PiecePtr Board::move(PiecePtr& piece, Position& position)
{
	
	auto pieceEaten = moveTry(piece,position);
	try
	{
		verifieCheck(piece->getColor());

		auto pawn = dynamic_cast<Pawn*>(piece.get());
		if (pawn && (position.second == 0 || position.second == NROWS))
			throw Promotion(piece);
		
		auto king = dynamic_cast<King*>(piece.get());
		auto castlingPosition =  std::find(castlingPositions_.begin(),castlingPositions_.end(),position);
		//castleling
		if (king && castlingPosition != castlingPositions_.end())
			castling(position, king);

		//condition for castling
		auto rook = dynamic_cast<Rook*>(piece.get());
		if (king)
			king->moved();
		if (rook)
		{
			if (rook->getPosition() == Position{ 1,1 })
				kingColor1_->bigCastlingRookMoved();
			if (rook->getPosition() == Position{ 8,1 })
				kingColor1_->smallCastlingRookMoved();
			if (rook->getPosition() == Position{ 8,8 })
				kingColor2_->smallCastlingRookMoved();
			if (rook->getPosition() == Position{ 1,8 })
				kingColor2_->bigCastlingRookMoved();
		}
		
		piece->setPosition(position);
	}
	catch (const Check&)
	{
		pieces_.insert({ piece->getPosition(), piece });
		pieces_.erase(position);
		if (pieceEaten != pieceNotFound)
			pieces_.insert({ pieceEaten->getPosition(), pieceEaten });
		throw ImpossibleMove();
	}
	verifieCheck(getOpponentColor(piece->getColor()));
	return pieceEaten;
}


PiecePtr Board::moveTry(PiecePtr& piece, Position& position)
{
	auto moves = piece->getMoves();
	auto it = std::find_if(moves.begin(), moves.end(), [&position](Position possiblePosition)->bool {return possiblePosition == position; });

	if (it == moves.end())
		throw ImpossibleMove();

	PiecePtr pieceEaten = getPiece(position);

	if (pieceEaten != pieceNotFound)
		pieces_.erase(position);

	pieces_.erase(piece->getPosition());
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
	PiecePtr piece = pieceNotFound;
	try
	{
		piece = pieces_.at(position);
	}
	catch (const std::out_of_range&)
	{
		piece = pieceNotFound;
	}

	return piece;
}

PiecePtr Board::getPiece(Position&& position)
{
	return getPiece(position);
}

bool Board::isUnoccupied(Position& position)
{
	return getPiece(position)== pieceNotFound;
}

bool Board::isUnoccupied(Position&& position)
{
	return isUnoccupied(position);
}


bool Board::isOccupiedByOtherColor(Position& position, const std::string& color)
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
	if (dynamic_cast<King*>(pieceToAdd.get()))
	{
		if (nKing_ == 1 && kingColorInserted == pieceToAdd->getColor())
			throw NotTwoKings("King inserted was the same color");
		nKing_++;
		kingColorInserted = pieceToAdd->getColor();
	}
	if (nKing_ > 2)
		throw NotTwoKings("Too many kings inserted in the board");

	if (getPiece(pieceToAdd->getPosition()) == pieceNotFound)
		pieces_.insert({ pieceToAdd->getPosition(), pieceToAdd });
	else
		std::cout << "Already a piece at position " << pieceToAdd->getPosition().first << ", " << pieceToAdd->getPosition().second << std::endl;
}


void Board::addPieces(std::vector<PiecePtr>&& piecesToAdd)
{
	for (auto&& piece : piecesToAdd)
		addPiece(piece);
}


void Board::verifieCheck(const std::string& color)
{

	auto king = std::find_if(pieces_.begin(), pieces_.end(),
		[&color](auto it)->bool {return color == it.second->getColor()&&dynamic_cast<King*>(it.second.get()); });
	if (king == pieces_.end())
		throw NotTwoKings("Required two kings to move");

	auto kingPosition = king->first;
				
	if (isCheckable(kingPosition, color))
	{
		throw Check(color);
	}
			

}



std::string Board::getOpponentColor(const std::string& color)
{
	return color == COLORPLAYER1 ? COLORPLAYER2 : COLORPLAYER1;
}

bool Board::isCheckable(Position& position ,const std::string& color)
{

	for (auto&& [positionKey, piece] : pieces_)
	{
		auto king = dynamic_cast<King*>(piece.get());
		if (king || piece->getColor()==color)
			continue;

		auto moves = piece->getMoves();
		auto positionOfPieceCheck = std::find_if(moves.begin(), moves.end(),
			[&position](Position positionParam)->bool {return position == positionParam; });

		if (positionOfPieceCheck != moves.end())
			return true;
	}
	return false;
}

bool Board::isCheckable(Position&& position,const std::string& color)
{
	return isCheckable(position, color);
}

void Board::castling(Position& position, King* king)
{
	if (position == Position{ 7,1 })
	{  
		PiecePtr rook = getPiece({ 8,1 });
		move(rook, {6,1});
	}
	if (position == Position{ 3,1 })
	{
		PiecePtr rook = getPiece({ 1,1 });
		move(rook, { 4,1 });
	}
	if (position == Position{ 7,8 })
	{
		PiecePtr rook = getPiece({ 8,8 });
		move(rook, { 6,8 });
	}
	if (position == Position{ 3,8 })
	{
		PiecePtr rook = getPiece({ 1,8 });
		move(rook, { 4,8 });
	}
}




