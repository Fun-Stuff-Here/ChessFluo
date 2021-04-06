#pragma once
#include "Piece.h"


namespace ChessModel
{
	class King : public Piece
	{
	public:
		King(Position& position, std::string& color, std::shared_ptr<Board> board);
		~King() = default;
		std::vector<Position> getMoves() const override;

	private:

	};
}