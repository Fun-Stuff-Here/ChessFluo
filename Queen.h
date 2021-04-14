/*
* Définition de la Classe Queen, Projet-INF1015
*\file		Queen.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once
#include "Piece.h"
#include "Board.h"

namespace ChessModel
{
	class Queen : public Piece
	{
	public:
		Queen(Position& position, std::string& color, Board* board);
		~Queen() = default;
		std::vector<Position> getMoves() const override;


	};
}