/*
* D�finition de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.hpp
*\author	Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544, Afaf Djellabi 2089967 
*\date		13 avril 2021
* Cr�� le	13 avril 2021
*/
#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
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
		
		void selections(ChessModel::PiecePtr& piece);

	public slots:


	private:
		//template <typename T = decltype(nullptr)>
		//QPushButton* nouveauBouton(const QString & text, const T & slot = nullptr);

		BoardPtr board_;  // Le Mod�le (pourrait �tre un pointeur mais pas n�cessaire dans ce cas).
		std::unordered_map<ChessModel::Position, ChessBoxPtr, ChessModel::pair_hash> chessBoxes_;
		ChessModel::PiecePtr selectedPiece_;


	};
}



