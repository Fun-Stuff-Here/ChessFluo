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

#include "Board.h"

namespace ChessModel {



	class Move
	{
	public:
		Move(mapPieces& pieces, Position& from, Position& to);

		Position getFrom() const ;
		Position getTo() const ;
		PiecePtr getPieceEated() const ;
		mapPieces getPieces() const ;
		bool isValid() const;

		virtual void execute()=0;

		virtual ~Move()=default;

	protected:
		mapPieces pieces_;
		Position from_;
		Position to_;
		PiecePtr eated_;
		bool isValid_;
	};

	class RegularMove: public Move
	{
	public:
		RegularMove(mapPieces & pieces, Position & from, Position & to);
		~RegularMove() = default;

		void execute() override;

	private:

	};

	class CastlingMove: public Move
	{
	public:
		CastlingMove(mapPieces& pieces, Position& from, Position& to);
		~CastlingMove() = default;

		void execute() override;

	};

	class PromotionMove: public Move
	{
	public:
		PromotionMove(mapPieces& pieces, Position& from, Position& to);
		~PromotionMove() = default;

		void execute() override;

	private:

	};

	class SpecialPawnMove : public Move
	{
	public:
		SpecialPawnMove(mapPieces& pieces, Position& from, Position& to);
		~SpecialPawnMove() = default;

		void execute() override;

	private:

	};


	using MovePtr = std::shared_ptr<Move>;
}
