/*
* Implémentation de la Classe Pawn, Projet-INF1015
*\file		Pawn.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/

#include "Pawn.h"

using namespace ChessModel;


Pawn::Pawn(Position& position, std::string& color, Board* board) :
	Piece(position, color, board)
{}


std::vector<Position> Pawn::getMoves() const
{
	std::vector<Position> positions;

	return positions;
}