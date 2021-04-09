#pragma once

#include "Pieces.h"
#include <unordered_map>
#include <memory>

namespace ChessModel
{
	//https://www.techiedelight.com/use-std-pair-key-std-unordered_map-cpp/
	struct pair_hash
	{
		template <class T1, class T2>
		std::size_t operator() (const std::pair<T1, T2>& pair) const
		{
			return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
		}
	};

	using PiecePtr = std::shared_ptr<Piece>;
	using mapPieces = std::unordered_map<Position, PiecePtr, pair_hash>;

	class Board
	{
	public:
		Board();
		~Board()=default;
		PiecePtr move(PiecePtr& piece, Position& position);// return eaten piece or nullptr if nothing
		PiecePtr move(PiecePtr& piece, Position&& position);// return eaten piece or nullptr if nothing
		mapPieces getPieces();
		PiecePtr getPiece(Position& position);
		PiecePtr getPiece(Position&& position);
		bool isUnoccupied(Position& position);
		bool isOccupiedByOtherColor(Position& position, std::string color);
		void addPiece(PiecePtr& pieceToAdd);

	private:
		mapPieces pieces_;

	};
}



