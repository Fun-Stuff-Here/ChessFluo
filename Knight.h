#pragma once
#include "Piece.h"

namespace ChessModel
{

	class Knight : public Piece
	{
	public:
		Knight(Position& position, std::string& color, std::shared_ptr<Board> board);
		~Knight() = default;
		std::vector<Position> getMoves() const override;

	private:

	};

}
