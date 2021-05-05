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

	class PositionView : public QWidget {
		Q_OBJECT

	public:
		PositionView(QWidget* parent = nullptr);
		~PositionView() override = default;

	public slots:

	private:

	};
}