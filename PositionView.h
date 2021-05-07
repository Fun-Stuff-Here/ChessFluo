//* \file		BoardView.hpp
//* \author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
//* \date		5 mai 2021
//* Créé le	5 mai 2021
//* /

#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <qwidget.h>
#include <QString>
#include <QLabel>
#pragma pop()

#include "Game.h"
#include "BoardView.h"


namespace ChessView {

	class PositionView : public QWidget {
		Q_OBJECT

	public:
		PositionView(ChessModel::GamePtr& game, QWidget* parent = nullptr);
		~PositionView() override = default;

	public slots:
		void regularStart();
		void puzzle1();
		void puzzle2();
		void puzzle3();
		void puzzle4();

	signals:
		void updateBoard();


	private:
			ChessModel::GamePtr game_;
			//BoardView boardView_;

	};
}