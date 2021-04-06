#pragma once
#include <utility>
#include <vector>
#include <string>
#include "NotImplemented.h"
//#include "Board.h"
#include <memory>



namespace ChessModel
{
	using Position = std::pair<int,int>;
	class Board;
	class Piece
	{
	public:
		static constexpr int topLimit = 8;
		static constexpr int bottomLimit = 1;

		Piece(Position& position, std::string& color, std::shared_ptr<Board> board);
		virtual ~Piece() = default;
		virtual std::vector<Position> getMoves() const = 0;
		Position getPosition() const;
		std::string getColor() const;


	protected:
		Position position_;
		std::string color_;
		std::shared_ptr<Board> board_;
		static bool isOutofBound(Position position);
	};

}
