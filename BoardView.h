/*
* Définition de la Classe BoardView, Projet-INF1015
*\file		BoardView.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#pragma once


#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <qwidget.h>
#include <QString>
#include <QLabel>
#pragma pop()

#include "Board.h"
#include "ChessBox.h"


namespace ChessView {

	using BoardPtr = std::shared_ptr<ChessModel::Board>;
	using ChessBoxPtr = std::shared_ptr<ChessBox>;


	class BoardView: public QWidget
	{
		Q_OBJECT


	public:
		BoardView(QWidget* parent = nullptr);
		~BoardView() override = default;

		void selections(ChessModel::PiecePtr& piece, ChessBox* chessbox);
		void update();
		void update(std::vector<ChessModel::Position>& positions, const double opacity);
		ChessModel::PiecePtr move(ChessModel::Position& position);

	public slots:


	private:
		BoardPtr board_;
		std::unordered_map<ChessModel::Position, ChessBoxPtr, ChessModel::pair_hash> chessBoxes_;
		ChessModel::PiecePtr selectedPiece_;

		bool isMoving(ChessModel::PiecePtr& piece);
		bool isSamePiece(ChessModel::PiecePtr& piece);



	};

}

