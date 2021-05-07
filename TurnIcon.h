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

namespace ChessView {

	class TurnIcon : public QPushButton {
		Q_OBJECT

	public:
		TurnIcon(ChessModel::GamePtr game, QWidget* parent = nullptr);
		~TurnIcon() = default;

	public slots:
		void update();

	private:
		ChessModel::GamePtr game_;
	};

	using TurnIconPtr = std::shared_ptr<TurnIcon>;
}
