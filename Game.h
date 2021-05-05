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
		Game();
		~Game() =default;




		bool isEnded();


		void start(Regular2PlayerGame);
		void start(REgular1PlayerGame);
		void start(WhiteToCheckMate1);
		void start(WhiteToCheckMate2);
		void start(WhiteToWin1);
		void start(WhiteToWin2);
		void start();



		bool isCheckMate(const std::string& color);

		void verifieCheck(const std::string& color);

		std::vector<MovePtr> getAllMovesPositions(const std::string& color);

		Board* getBoard();

		std::string getTurn() const;


		PiecePtr move(PiecePtr& piece, Position& position);
		PiecePtr move(PiecePtr& piece, Position&& position);

		MovePtr moveTry(PiecePtr& piece, Position& position);


		bool isValidMove(Position& from, Position& to);
		std::vector<Position> getMovesPositions(Position& position);
		std::vector<Position> getMovesPositions(Position&& position);

	private:
		std::string turn_;
		Board board_;
		std::vector<MovePtr> moveHistory_;
		bool isFinished_;
		//std::vector<Player> players;

	};

}


