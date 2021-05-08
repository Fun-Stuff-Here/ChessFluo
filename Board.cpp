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
	fill();
}

Board::Board(Empty)
{
}

Board::Board(KingOnly)
{
	fill(KingOnly{});
}


void Board::fill(KingOnly)
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

void Board::fill()
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
		positionRookLeft1{ 1,1 },
		positionRookRight1{ 8,1 },
		positionRookLeft2{ 1,8 },
		positionRookRight2{ 8,8 },
		positionQueen1{ 4,1 },
		positionQueen2{ 4,8 };


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
		rookLeft1(new Rook{ positionRookLeft1,colorPlayer1,this }),
		rookRight1(new Rook{ positionRookRight1,colorPlayer1,this }),
		rookLeft2(new Rook{ positionRookLeft2,colorPlayer2,this }),
		rookRight2(new Rook{ positionRookRight2,colorPlayer2,this }),
		queen1(new Queen{ positionQueen1,colorPlayer1,this }),
		queen2(new Queen{ positionQueen2,colorPlayer2,this });

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
	for (size_t i : iter::range(NROWS))
	{
		Position position{ i + 1,2 };
		PiecePtr pawn(new Pawn{ position , colorPlayer1,this });
		addPiece(pawn);
	}
	//pawn player2
	for (size_t i : iter::range(NCOLUMNS))
	{
		Position position{ i + 1,7 };
		PiecePtr pawn(new Pawn{ position , colorPlayer2,this });
		addPiece(pawn);
	}

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



bool Board::hasTwoKings()
{
	return nKing_ == 2;
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
	if (rookPositionTo != Position{ 0,0 } && dynamic_cast<Rook*>(rook.get()))
	{
		pieces_.erase(rook->getPosition());
		pieces_.insert({ rookPositionTo, rook });
		rook->setPosition(rookPositionTo);
	}

}


void Board::restore(MovePtr& move)
{
	auto pieces = move->getPieces();
	restore(pieces);
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


void Board::removePiece(Position& position)
{
	pieces_.erase(position);
}

void Board::clearPieces()
{
	pieces_.clear();
	nKing_ = 0;
	kingColorInserted = "";
}

void Board::fill(WhiteToCheckMate1)
{
	std::string white = COLORPLAYER1;
	std::string black = COLORPLAYER2;

	Position blackRookPosition{ 1,8 },
		blackQueenPosition{ 1,6 },
		blackPawn1Position{ 2,5 },
		blackPawn2Position{ 3,4 },
		blackKnight1Position{ 3,5 },
		blackBishop1Position{ 4,7 },
		blackBishop2Position{ 5,7 },
		blackPawn3Position{ 5,5 },
		blackPawn4Position{ 6,6 },
		blackKnight2Position{ 7,5 },
		blackKingPosition{ 7,7 },
		blackPawn5Position{ 8,5 },
		blackPawn6Position{ 8,7 },
		whitePawn1Position{ 2,2 },
		whiteBishop1Position{ 3,1 },
		whiteBishop2Position{ 3,2 },
		whitePawn2Position{ 3,3 },
		whitePawn3Position{ 4,5 },
		whiteRookPosition{ 6,1 },
		whiteKingPosition{ 7,1 },
		whitePawn4Position{ 7,2 },
		whiteQueenPosition{ 8,4 },
		whiteKnight1Position{ 8,6 };


	PiecePtr blackRook{ new Rook{blackRookPosition,black,this} },
		blackQueen{ new Queen{blackQueenPosition,black,this} },
		blackPawn1{ new Pawn{blackPawn1Position,black,this} },
		blackPawn2{ new Pawn{blackPawn2Position,black,this} },
		blackKnight1{ new Knight{blackKnight1Position,black, this} },
		blackBishop1{ new Bishop{blackBishop1Position,black,this} },
		blackBishop2{ new Bishop{blackBishop2Position,black,this} },
		blackPawn3{ new Pawn{blackPawn3Position,black,this} },
		blackPawn4{ new Pawn{blackPawn4Position,black,this} },
		blackKnight2{ new Knight{blackKnight2Position,black,this} },
		blackKing{ new King{blackKingPosition, black, this} },
		blackPawn5{ new Pawn{blackPawn5Position,black,this} },
		blackPawn6{ new Pawn{blackPawn6Position,black,this} },
		whitePawn1{ new Pawn{whitePawn1Position,white,this} },
		whiteBishop1{ new Bishop{whiteBishop1Position,white,this} },
		whiteBishop2{ new Bishop{whiteBishop2Position,white,this} },
		whitePawn2{ new Pawn{whitePawn2Position,white,this} },
		whitePawn3{ new Pawn{whitePawn3Position,white,this} },
		whiteRook{ new Rook{whiteRookPosition,white,this} },
		whiteKing{ new King{whiteKingPosition,white,this} },
		whitePawn4{ new Pawn{whitePawn4Position,white,this} },
		whiteQueen{ new Queen{whiteQueenPosition,white,this} },
		whiteKnight1{ new Knight{whiteKnight1Position,white,this } };

	addPieces({
		blackRook,
		blackQueen,
		blackPawn1,
		blackPawn2,
		blackKnight1,
		blackBishop1,
		blackBishop2,
		blackPawn3,
		blackPawn4,
		blackKnight2,
		blackKing,
		blackPawn5,
		blackPawn6,
		whitePawn1,
		whiteBishop1,
		whiteBishop2,
		whitePawn2,
		whitePawn3,
		whiteRook,
		whiteKing,
		whitePawn4,
		whiteQueen,
		whiteKnight1
		});

	kingColor1_ = dynamic_cast<King*>(whiteKing.get());
	kingColor2_ = dynamic_cast<King*>(blackKing.get());
}


void Board::fill(WhiteToCheckMate2)
{
	std::string white = COLORPLAYER1;
	std::string black = COLORPLAYER2;

	Position blackRookPosition{ 1,8 },
		blackPawn1Position{ 1,7 },
		blackPawn2Position{ 2,7 },
		blackKnight1Position{ 4,8 },
		blackBishop1Position{ 3,6 },
		blackPawn3Position{ 3,4 },
		blackPawn4Position{ 4,6 },
		blackKingPosition{ 8,8 },
		blackPawn5Position{ 7,7 },
		blackPawn6Position{ 8,7 },
		whitePawn1Position{ 1,2 },
		whiteBishop1Position{ 4,5 },
		whitePawn2Position{ 3,3 },
		whitePawn3Position{ 4,4 },
		whiteRookPosition{ 5,7 },
		whiteKingPosition{ 7,1 },
		whitePawn4Position{ 6,5 },
		whiteKnight1Position{ 7,5 },
		whitePawn5Position{8,2};


	PiecePtr blackRook{ new Rook{blackRookPosition,black,this} },
		blackPawn1{ new Pawn{blackPawn1Position,black,this} },
		blackPawn2{ new Pawn{blackPawn2Position,black,this} },
		blackKnight1{ new Knight{blackKnight1Position,black, this} },
		blackBishop1{ new Bishop{blackBishop1Position,black,this} },
		blackPawn3{ new Pawn{blackPawn3Position,black,this} },
		blackPawn4{ new Pawn{blackPawn4Position,black,this} },
		blackKing{ new King{blackKingPosition, black, this} },
		blackPawn5{ new Pawn{blackPawn5Position,black,this} },
		blackPawn6{ new Pawn{blackPawn6Position,black,this} },
		whitePawn1{ new Pawn{whitePawn1Position,white,this} },
		whiteBishop1{ new Bishop{whiteBishop1Position,white,this} },
		whitePawn2{ new Pawn{whitePawn2Position,white,this} },
		whitePawn3{ new Pawn{whitePawn3Position,white,this} },
		whiteRook{ new Rook{whiteRookPosition,white,this} },
		whiteKing{ new King{whiteKingPosition,white,this} },
		whitePawn4{ new Pawn{whitePawn4Position,white,this} },
		whiteKnight1{ new Knight{whiteKnight1Position,white,this } },
		whitePawn5{ new Pawn{whitePawn5Position,white,this} };

	addPieces({
		blackRook,
		blackPawn1,
		blackPawn2,
		blackKnight1,
		blackBishop1,
		blackPawn3,
		blackPawn4,
		blackKing,
		blackPawn5,
		blackPawn6,
		whitePawn1,
		whiteBishop1,
		whitePawn2,
		whitePawn3,
		whiteRook,
		whiteKing,
		whitePawn4,
		whiteKnight1,
		whitePawn5
		});

	kingColor1_ = dynamic_cast<King*>(whiteKing.get());
	kingColor2_ = dynamic_cast<King*>(blackKing.get());
}


void Board::fill(WhiteToWin1) 
{
	std::string white = COLORPLAYER1;
	std::string black = COLORPLAYER2;

	Position blackRookPosition{ 5,8 },
		blackRook2Position{3,2},
		blackQueenPosition{ 6,7 },
		blackPawn1Position{ 1,7 },
		blackPawn2Position{ 2,6 },
		blackBishop1Position{ 2,7 },
		blackPawn3Position{ 5,3 },
		blackPawn4Position{ 7,6 },
		blackKingPosition{ 7,8 },
		blackPawn5Position{ 8,7 },
		whitePawn1Position{ 1,2 },
		whiteBishop1Position{ 7,7 },
		whitePawn2Position{ 2,2 },
		whitePawn3Position{ 4,4 },
		whiteRookPosition{ 1,1 },
		whiteRook2Position{ 6,4 },
		whiteKingPosition{ 7,1 },
		whitePawn4Position{ 6,6 },
		whiteQueenPosition{ 8,4 },
		whitePawn5Position{7,2},
		whitePawn6Position{ 8,2 };


	PiecePtr blackRook{ new Rook{blackRookPosition,black,this} },
		blackRook2{ new Rook{blackRook2Position,black,this} },
		blackQueen{ new Queen{blackQueenPosition,black,this} },
		blackPawn1{ new Pawn{blackPawn1Position,black,this} },
		blackPawn2{ new Pawn{blackPawn2Position,black,this} },
		blackBishop1{ new Bishop{blackBishop1Position,black,this} },
		blackPawn3{ new Pawn{blackPawn3Position,black,this} },
		blackPawn4{ new Pawn{blackPawn4Position,black,this} },
		blackKing{ new King{blackKingPosition, black, this} },
		blackPawn5{ new Pawn{blackPawn5Position,black,this} },
		whitePawn1{ new Pawn{whitePawn1Position,white,this} },
		whiteBishop1{ new Bishop{whiteBishop1Position,white,this} },
		whitePawn2{ new Pawn{whitePawn2Position,white,this} },
		whitePawn3{ new Pawn{whitePawn3Position,white,this} },
		whiteRook{ new Rook{whiteRookPosition,white,this} },
		whiteRook2{ new Rook{whiteRook2Position,white,this} },
		whiteKing{ new King{whiteKingPosition,white,this} },
		whitePawn4{ new Pawn{whitePawn4Position,white,this} },
		whiteQueen{ new Queen{whiteQueenPosition,white,this} },
		whitePawn5{ new Pawn{whitePawn5Position,white,this} },
		whitePawn6{ new Pawn{whitePawn6Position,white,this} };

	addPieces({
		blackRook,
		blackRook2,
		blackQueen,
		blackPawn1,
		blackPawn2,
		blackBishop1,
		blackPawn3,
		blackPawn4,
		blackKing,
		blackPawn5,
		whitePawn1,
		whiteBishop1,
		whitePawn2,
		whitePawn3,
		whiteRook,
		whiteRook2,
		whiteKing,
		whitePawn4,
		whiteQueen,
		whitePawn5,
		whitePawn6
		});

	kingColor1_ = dynamic_cast<King*>(whiteKing.get());
	kingColor2_ = dynamic_cast<King*>(blackKing.get());
}


void Board::fill(WhiteToWin2)
{
	std::string white = COLORPLAYER1;
	std::string black = COLORPLAYER2;

	Position blackRookPosition{ 3,8 },
		blackQueenPosition{ 5,2 },
		blackPawn1Position{ 1,7 },
		blackPawn2Position{ 2,7 },
		blackBishop1Position{ 8,6 },
		blackPawn3Position{ 5,4 },
		blackPawn4Position{ 8,7 },
		blackKingPosition{ 1,8 },
		whitePawn1Position{ 1,2 },
		whiteBishop1Position{ 3,1 },
		whitePawn2Position{ 2,2 },
		whitePawn3Position{ 3,2 },
		whiteRookPosition{ 4,1 },
		whiteKingPosition{ 2,1 },
		whitePawn4Position{ 5,3 },
		whiteQueenPosition{ 5,5 };


	PiecePtr blackRook{ new Rook{blackRookPosition,black,this} },
		blackQueen{ new Queen{blackQueenPosition,black,this} },
		blackPawn1{ new Pawn{blackPawn1Position,black,this} },
		blackPawn2{ new Pawn{blackPawn2Position,black,this} },
		blackBishop1{ new Bishop{blackBishop1Position,black,this} },
		blackPawn3{ new Pawn{blackPawn3Position,black,this} },
		blackPawn4{ new Pawn{blackPawn4Position,black,this} },
		blackKing{ new King{blackKingPosition, black, this} },
		whitePawn1{ new Pawn{whitePawn1Position,white,this} },
		whiteBishop1{ new Bishop{whiteBishop1Position,white,this} },
		whitePawn2{ new Pawn{whitePawn2Position,white,this} },
		whitePawn3{ new Pawn{whitePawn3Position,white,this} },
		whiteRook{ new Rook{whiteRookPosition,white,this} },
		whiteKing{ new King{whiteKingPosition,white,this} },
		whitePawn4{ new Pawn{whitePawn4Position,white,this} },
		whiteQueen{ new Queen{whiteQueenPosition,white,this} };

	addPieces({
		blackRook,
		blackQueen,
		blackPawn1,
		blackPawn2,
		blackBishop1,
		blackPawn3,
		blackPawn4,
		blackKing,
		whitePawn1,
		whiteBishop1,
		whitePawn2,
		whitePawn3,
		whiteRook,
		whiteKing,
		whitePawn4,
		whiteQueen
		});

	kingColor1_ = dynamic_cast<King*>(whiteKing.get());
	kingColor2_ = dynamic_cast<King*>(blackKing.get());
}