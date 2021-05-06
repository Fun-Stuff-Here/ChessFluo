#pragma once
//* \file		BoardView.hpp
//* \author	Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544, Afaf Djellabi 2089967
//* \date		5 mai 2021
//* Cr�� le	5 mai 2021
//* /

#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <qwidget.h>
#include <QString>
#include <QLabel>
#pragma pop()

#include "Game.h"

namespace ChessView {

	class FeaturesView : public QWidget {
		Q_OBJECT

	public:
		FeaturesView(ChessModel::GamePtr& game, QWidget* parent = nullptr);
		~FeaturesView() override = default;

	public slots:
		void start();
		void undo();
		void redo();
		void reset();


	private:
		ChessModel::GamePtr game_;

	};
}