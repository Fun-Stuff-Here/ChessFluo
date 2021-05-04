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

using namespace ChessModel;



Move::Move(mapPieces& pieces, Position& from, Position& to):
	pieces_(pieces), from_(from), to_(to) {}

Position Move::getFrom() const
{
	return from_;
}

Position Move::getTo() const
{
	return to_;
}

PiecePtr Move::getPieceEated() const
{
	return eated_;
}

mapPieces Move::getPieces() const
{
	return pieces_;
}


bool Move::isValid() const
{
	return isValid_;
}

RegularMove::RegularMove(mapPieces& pieces, Position& from, Position& to):
	Move(pieces,from,to){}


void RegularMove::execute()
{
	throw NotImplemented();
}