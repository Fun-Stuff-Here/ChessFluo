/*
* Définition de la Classe Board, Projet-INF1015
*\file		Board.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once

#include "Piece.h"
#include <unordered_map>
#include <memory>
#include "Move.h"

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

	using mapPieces = std::unordered_map<Position, PiecePtr, pair_hash>;


	struct Empty
	{};
	struct KingOnly
	{};

	class Board
	{
	public:
		Board();
		Board(Empty);
		Board(KingOnly);
		~Board()=default;


		MovePtr move(PiecePtr& piece, Position& position);// return eaten piece or nullptr if nothing
		MovePtr move(PiecePtr& piece, Position&& position);// return eaten piece or nullptr if nothing



		mapPieces getPieces();
		PiecePtr getPiece(Position& position);
		PiecePtr getPiece(Position&& position);
		void addPiece(PiecePtr& pieceToAdd);
		void addPieces(std::vector<PiecePtr>&& piecesToAdd);


		bool isUnoccupied(Position& position);
		bool isUnoccupied(Position&& position);
		bool isOccupiedByOtherColor(Position& position, const std::string& color);

		std::string getOpponentColor(const std::string& color);


		inline static const PiecePtr pieceNotFound = nullptr;

		void restore(MovePtr& move);


	private:




		mapPieces pieces_;
		int nKing_ = 0;
		std::string kingColorInserted;
		class King* kingColor1_;
		class King* kingColor2_;
		const std::vector<Position> castlingPositions_ = {
			{7,1},
			{3,1},
			{7,8},
			{3,8}
		};

		void castling(Position&position, class King* king);

	};
}



