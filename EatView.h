//* \file		EatViw.hpp
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
#include "PieceIcon.h"

namespace ChessView {

	class EatView : public QWidget {
		Q_OBJECT

	public:
		EatView(ChessModel::GamePtr& game, QWidget* parent = nullptr);
		~EatView() override = default;

	public slots:
		void update();
	
	signals:
		void iconUpdate(ChessModel::PiecePtr piece);

	private:
		ChessModel::GamePtr game_;
		std::map<std::string, std::vector<PieceIconPtr>> eatenPiecesIcons_;
		int nPiece_;

	};
}