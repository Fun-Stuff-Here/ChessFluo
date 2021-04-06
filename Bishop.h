#pragma once
#include "Piece.h"


namespace ChessModel
{
	class Bishop : public Piece
	{
	public:
		Bishop(Position& position, std::string& color, std::shared_ptr<Board> board);
		~Bishop() = default;
		std::vector<Position> getMoves() const override;

	private:

	};
}