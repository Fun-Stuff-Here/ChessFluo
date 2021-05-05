#pragma once
/*
* Définition de la Classe Momento, Projet-INF1015
*\file		Momento.h
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once

#include<memory>

#include "Piece.h"

namespace ChessModel {

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




	class Move
	{
	public:
		Move(mapPieces& pieces, Position& from, Position& to);
		Move() = default;

		Position getFrom() const ;
		Position getTo() const ;
		PiecePtr getPieceEat() const ;
		mapPieces getPieces() const ;

		virtual void execute(class Game* game) = 0;

		virtual ~Move()=default;

	protected:
		mapPieces pieces_;
		Position from_;
		Position to_;
		PiecePtr eat_;
	};

	class RegularMove: public Move
	{
	public:
		RegularMove(mapPieces & pieces, Position & from, Position & to);
		~RegularMove() = default;

		void execute(class Game* game) override;

	private:

	};

	class CastlingMove: public Move
	{
	public:
		CastlingMove(mapPieces& pieces, Position& from, Position& to);
		~CastlingMove() = default;

		void execute(class Game* game) override;

	};

	class PromotionMove: public Move
	{
	public:
		PromotionMove(mapPieces& pieces, Position& from, Position& to);
		~PromotionMove() = default;

		void execute(class Game* game) override;

	private:

	};

	


	using MovePtr = std::shared_ptr<Move>;
}
