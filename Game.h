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
#include <set>

namespace ChessModel {


	class Game
	{
	public:
		Game();
		~Game() =default;




		bool isEnded();


		void start(Regular2PlayerGame);
		void start(Regular1PlayerGame);
		void start(WhiteToCheckMate1);
		void start(WhiteToCheckMate2);
		void start(WhiteToWin1);
		void start(WhiteToWin2);
		void start();


		std::set<PiecePtr> getPieceEat() const;

		bool canUndo() const;
		bool canRedo() const;

		void undo();
		void redo();


		bool isCheckMate(const std::string& color);

		void verifieCheck(const std::string& color);

		std::vector<MovePtr> getAllMovesPositions(const std::string& color);

		Board* getBoard();

		std::string getTurn() const;
		void changeTurn();

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
		std::vector<MovePtr> redoHistory_;
		std::set<PiecePtr> piecesEat_;
		bool isFinished_;

		void redoClear();

	};

	using GamePtr = std::shared_ptr<Game>;

}


