/*
* D�finition de la Classe King, Projet-INF1015
*\file		King.hpp
*\author	Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544
*\date		12 avril 2021
* Cr�� le	10 avril 2021
*/
#pragma once
#include "Piece.h"
#include "Board.h"

namespace ChessModel
{
	class King : public Piece
	{
	public:
		King(Position& position, std::string& color, Board* board);
		~King() = default;
		std::vector<Position> getMoves() const override;

	private:

	};
}