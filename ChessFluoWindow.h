/*
* Définition de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967 
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma pop()

#include "Board.h"
#include "ChessBox.h"


namespace ChessView
{
	
	
	using BoardPtr = std::shared_ptr<ChessModel::Board>;
	using ChessBoxPtr = std::shared_ptr<ChessBox>;
	class ChessFluoWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		ChessFluoWindow(QWidget* parent = nullptr);
		~ChessFluoWindow() override = default;
		
		void selections(ChessModel::PiecePtr& piece, ChessBox* chessbox);
		void update();
		void update(std::vector<ChessModel::Position>& positions, const double opacity);
		ChessModel::PiecePtr move(ChessModel::Position& position);

	public slots:


	private:
		BoardPtr board_;  // Le Modèle (pourrait être un pointeur mais pas nécessaire dans ce cas).
		std::unordered_map<ChessModel::Position, ChessBoxPtr, ChessModel::pair_hash> chessBoxes_;
		ChessModel::PiecePtr selectedPiece_;

		bool isMoving(ChessModel::PiecePtr& piece);
		bool isSamePiece(ChessModel::PiecePtr& piece);
	};
}



