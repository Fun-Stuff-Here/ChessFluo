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
