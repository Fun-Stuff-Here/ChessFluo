/*
* Définition des Classe Player, Projet-INF1015
*\file		Players.h
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544,Afaf Djellabi 2089967
*\date		12 avril 2021
* Créé le	10 avril 2021
*/

#pragma once

#include <string>
#include "Piece.h"

namespace ChessModel {
	class Player
	{
	public:
		std::string getColor() const;
		virtual PiecePtr makeMove(PiecePtr& piece, Position& position)=0;// return eaten piece or nullptr if nothing
		virtual PiecePtr makeMove(PiecePtr& piece, Position&& position)=0;// return eaten piece or nullptr if nothing

		Player(std::string& color);
		virtual ~Player() = default;

	private:
		std::string color_;
	};




	class HumainPlayer: public Player
	{
	public:
		HumainPlayer()=default;
		~HumainPlayer()=default;

	private:

	};

	class AIPlayer: public Player
	{
	public:
		AIPlayer()=default;
		~AIPlayer()=default;

	private:

	};


}


