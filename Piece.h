/*
* Définition de la Classe Piece, Projet-INF1015
*\file		Piece.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "Constant.h"


namespace ChessModel
{
	using Position = std::pair<int,int>;
	class Piece
	{
	public:
		static constexpr int topLimit = 8;
		static constexpr int bottomLimit = 1;

		Piece(Position& position, std::string& color, class Board* board);
		virtual ~Piece() = default;
		virtual std::vector<Position> getMoves() const = 0;
		Position getPosition() const;
		std::string getColor() const;
		void setPosition(Position& position);

	protected:
		Position position_;
		std::string color_;
		class Board* board_;
		bool isOutofBound(Position& position) const;
		void checkFilter(std::vector<Position>& positions);
	};

}
