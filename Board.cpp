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
#include <cppitertools/range.hpp>

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
		for(size_t i : iter::range(NROWS))
		{
			Position position{i+1,2};
			PiecePtr pawn(new Pawn{ position , colorPlayer1,this });
			addPiece(pawn);
		}
		//pawn player2
		for (size_t i: iter::range(NCOLUMNS))
		{
			Position position{ i+1,7 };
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

mapPieces Board::getPieces() const
{
	return pieces_;
}

PiecePtr Board::getPiece(Position& position) const
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

PiecePtr Board::getPiece(Position&& position) const
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






std::string Board::getOpponentColor(const std::string& color)
{
	return color == COLORPLAYER1 ? COLORPLAYER2 : COLORPLAYER1;
}



void Board::castling(Position& position, King* king)
{
	Position rookPositionTo{0,0};
	PiecePtr rook = pieceNotFound;
	if (position == Position{ 7,1 })
	{  
		rook = getPiece({ 8,1 });
		rookPositionTo = { 6,1 };
	}
	if (position == Position{ 3,1 })
	{
		rook = getPiece({ 1,1 });
		rookPositionTo =  { 4,1 };
	}
	if (position == Position{ 7,8 })
	{
		rook = getPiece({ 8,8 });
		rookPositionTo= { 6,8 };
	}
	if (position == Position{ 3,8 })
	{
		rook = getPiece({ 1,8 });
		rookPositionTo = { 4,8 };
	}
	if (rookPositionTo != Position{ 0,0 } && rook != pieceNotFound)
	{
		pieces_.erase(rook->getPosition());
		pieces_.insert({ rookPositionTo, rook });
		rook->setPosition(rookPositionTo);
	}

}


void Board::restore(MovePtr& move)
{
	pieces_ = move->getPieces();
	Position from = move->getFrom();
	Position to = move->getTo();
	PiecePtr pieceMoved = pieces_.at(to);
	PiecePtr pieceEated = move->getPieceEat();

	pieces_[from] = pieceMoved;
	pieces_.erase(to);
	if (pieceEated)
		pieces_[to] = pieceEated;

}


King* Board::getKing(const std::string& color) const
{
	return color == COLORPLAYER1 ? kingColor1_ : kingColor2_;
}


mapPieces Board::save() const
{
	return pieces_;
}

void Board::restore(mapPieces& save)
{
	pieces_ = save;
	for (auto&& it : pieces_)
		it.second->setPosition(it.first);
}



bool Board::isCheckable(Position& position, const std::string& color)
{
	for (auto&& [positionKey, piece] :pieces_)
	{
		auto king = dynamic_cast<King*>(piece.get());
		if (king || piece->getColor() == color)
			continue;

		auto moves = piece->getMoves();
		auto positionOfPieceCheck = std::find_if(moves.begin(), moves.end(),
			[&position](Position positionParam)->bool {return position == positionParam; });

		if (positionOfPieceCheck != moves.end())
			return true;
	}
	return false;
}

bool Board::isCheckable(Position&& position, const std::string& color)
{
	return isCheckable(position, color);
}