/*
* Définition de la Classe ChessBox, Projet-INF1015
*\file		ChessBox.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QAbstractButton>
#include < QPushButton>
#include <QString>
#include <QLabel>
#include <qgroupbox.h>
#pragma pop()

#include <memory>
#include <vector>

#include "Board.h"


namespace ChessView
{
	using BoardPtr = std::shared_ptr<ChessModel::Board>;
	class ChessBox : public QPushButton
	{
		Q_OBJECT

	public slots:
		void selected();

	public:
		ChessBox(BoardPtr& board, ChessModel::Position& position,class ChessFluoWindow* boardView, QWidget* parent = nullptr);
		~ChessBox() = default;

		void update();
		ChessModel::Position getPosition();

	private:
		ChessModel::PiecePtr piece_;
		ChessModel::Position position_;
		BoardPtr board_;
		class ChessFluoWindow* boardView_;


	};
}




