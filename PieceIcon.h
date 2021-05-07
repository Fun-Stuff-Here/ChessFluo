//* \file		PieceIcon.hpp
//* \author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
//* \date		5 mai 2021
//* Créé le	5 mai 2021
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

	class PieceIcon : public QPushButton {
		Q_OBJECT

	public:
		PieceIcon(const std::string color, QWidget* parent = nullptr);
		~PieceIcon() = default;

		ChessModel::PiecePtr getPiece() const;

	public slots:
		void update(ChessModel::PiecePtr piece);

	private:
		ChessModel::PiecePtr piece_;
		std::string color_;


	};

	using PieceIconPtr = std::shared_ptr<PieceIcon>;
}