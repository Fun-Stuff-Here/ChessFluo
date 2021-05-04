/*
* Définition de la Classe Game, Projet-INF1015
*\file		Game.h
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544,Afaf Djellabi 2089967
*\date		12 avril 2021
* Créé le	10 avril 2021
*/


#pragma once
#include "Constant.h"

#include "Board.h"
#include "Move.h"
#include "Players.h"

namespace ChessModel {
	class Game
	{
	public:
		Game()=default;
		~Game() =default;
		bool isEnded();
		bool isCheckMate();

		bool isCheckable(Position&& position, const std::string& color);
		bool isCheckable(Position& position, const std::string& color);

		void verifieCheck(const std::string& color);





	private:
		std::string turn_;	//player class should be here instead
		Board board_;
		std::vector<MovePtr> moveHistory_;
		std::vector<Player> players;

	};

}


