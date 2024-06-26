/*
* D�finition de la Classe ChessBox, Projet-INF1015
*\file		ChessBox.hpp
*\author	Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Cr�� le	13 avril 2021
*/
#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QMainWindow>
#include <QAbstractButton>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <qgroupbox.h>
#pragma pop()

#include <memory>
#include <vector>

#include "Game.h"


namespace ChessView
{
	class ChessBox : public QPushButton
	{
		Q_OBJECT

	public slots:
		void selected();

	public:
		ChessBox(ChessModel::GamePtr& board, ChessModel::Position& position,class BoardView* boardView);
		~ChessBox() = default;
		
		void update();
		ChessModel::Position getPosition();

	private:
		ChessModel::PiecePtr piece_;
		ChessModel::Position position_;
		ChessModel::GamePtr game_;
		class BoardView* boardView_;


	};

	using ChessBoxPtr = std::shared_ptr<ChessBox>;
}




