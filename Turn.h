//* \file		Turn.hpp
//* \author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
//* \date	7 mai 2021
//* Créé le	7 mai 2021
//* /
#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <qwidget.h>
#include <QString>
#include <qlabel.h>
#include <QPushButton>
#pragma pop()

#include "Game.h"
#include "TurnIcon.h"

namespace ChessView {

	class Turn : public QWidget {
		Q_OBJECT

	public:
		Turn(ChessModel::GamePtr game, QWidget* parent = nullptr);
		~Turn() = default;

	public slots:
		void update();


	private:
		ChessModel::GamePtr game_;
		TurnIcon icon_;
	};

	using TurnPtr = std::shared_ptr<Turn>;
}