/*
* Implémentation de la Classe Move, Projet-INF1015
*\file		Move.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/

#include "Move.h"
#include "exeptions.h"
#include "Board.h"
#include "Game.h"
#include "King.h"
#include "Queen.h"

using namespace ChessModel;



Move::Move(mapPieces& pieces, Position& from, Position& to):
	pieces_(pieces), from_(from), to_(to) {}

RegularMove::RegularMove(mapPieces& pieces, Position& from, Position& to) :
	Move(pieces, from, to) {}

CastlingMove::CastlingMove(mapPieces& pieces, Position& from, Position& to) :
	Move(pieces, from, to) {}

PromotionMove::PromotionMove(mapPieces& pieces, Position& from, Position& to) :
	Move(pieces, from, to) {}




Position Move::getFrom() const
{
	return from_;
}

Position Move::getTo() const
{
	return to_;
}

PiecePtr Move::getPieceEat() const
{
	return eat_;
}

mapPieces Move::getPieces() const
{
	return pieces_;
}



void RegularMove::execute(Game* game)
{
	auto piece = pieces_.at(from_);
	eat_ = game->getBoard()->move(piece, to_);
	
}

void CastlingMove::execute(Game* game)
{
	auto piece = pieces_.at(from_);
	auto king = dynamic_cast<King*>(piece.get());
	eat_ = game->getBoard()->move(piece, to_);
	game->getBoard()->castling(to_, king);
}


void PromotionMove::execute(Game* game)
{
	auto piece = pieces_.at(from_);
	auto board = game->getBoard();
	eat_ = board->move(piece, to_);
	board->removePiece(to_);
	auto color = piece->getColor();
	PiecePtr queen(new Queen{to_,color,board });
	board->addPiece(queen);

}






