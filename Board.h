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

	struct Empty{};
	struct KingOnly{};
	struct Regular2PlayerGame {};
	struct Regular1PlayerGame {};
	struct WhiteToCheckMate1 {};
	struct WhiteToCheckMate2 {};
	struct WhiteToWin1 {};
	struct WhiteToWin2 {};


	class Board
	{
	public:
		Board();
		Board(Empty);
		Board(KingOnly);
		~Board()=default;


		PiecePtr move(PiecePtr& piece, Position& position);
		PiecePtr move(PiecePtr& piece, Position&& position);
		void castling(Position& position, class King* king);


		mapPieces getPieces() const;
		PiecePtr getPiece(Position& position) const;
		PiecePtr getPiece(Position&& position) const;
		class King* getKing(const std::string& color) const;


		void fill(KingOnly);
		void fill();
		void fill(WhiteToCheckMate1);
		void fill(WhiteToCheckMate2);
		void fill(WhiteToWin1);
		void fill(WhiteToWin2);

		void addPiece(PiecePtr& pieceToAdd);
		void addPieces(std::vector<PiecePtr>&& piecesToAdd);
		void removePiece(Position& position);
		void clearPieces();


		bool isUnoccupied(Position& position);
		bool isUnoccupied(Position&& position);
		bool isOccupiedByOtherColor(Position& position, const std::string& color);

		std::string getOpponentColor(const std::string& color);


		inline static const PiecePtr pieceNotFound = nullptr;

		void restore(MovePtr& move);

		mapPieces save() const;
		void restore(mapPieces& save);

		bool isCheckable(Position&& position, const std::string& color);
		bool isCheckable(Position& position, const std::string& color);

	private:

		mapPieces pieces_;

		int nKing_ = 0;
		std::string kingColorInserted;

		class King* kingColor1_;
		class King* kingColor2_;

	};
}



