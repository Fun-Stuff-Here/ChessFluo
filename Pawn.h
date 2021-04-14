/*
* Définition de la Classe Pawn, Projet-INF1015
*\file		Pawn.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once
#include "Piece.h"
#include "Board.h"

namespace ChessModel
{
	class Pawn : public Piece
	{
	public:
		Pawn(Position& position, std::string& color, Board* board);
		~Pawn() = default;
		std::vector<Position> getMoves() const override;


	};
}
