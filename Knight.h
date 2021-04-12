/*
* Définition de la Classe Knight, Projet-INF1015
*\file		Knight.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once
#include "Piece.h"
#include "Board.h"

namespace ChessModel
{

	class Knight : public Piece
	{
	public:
		Knight(Position& position, std::string& color, Board* board);
		~Knight() = default;
		std::vector<Position> getMoves() const override;

	private:

	};

}
