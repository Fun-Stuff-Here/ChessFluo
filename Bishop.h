/*
* Définition de la Classe Bishop, Projet-INF1015
*\file		Bishop.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once
#include "Piece.h"
#include "Board.h"

namespace ChessModel
{
	class Bishop : public Piece
	{
	public:
		Bishop(Position& position, std::string& color, Board* board);
		~Bishop() = default;
		std::vector<Position> getMoves() const override;

	private:

	};
}

