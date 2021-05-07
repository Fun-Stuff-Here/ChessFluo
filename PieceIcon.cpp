/*
* Implémentation de la Classe PiceIcon, Projet-INF1015
*\file		PiceIcon.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#include "PieceIcon.h"
#include "exeptions.h"
#include "Game.h"
#include "Constant.h"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <qgridlayout.h>
#include <QGraphicsOpacityEffect>
#include <qmessagebox.h>
#pragma pop()

using namespace ChessView;


PieceIcon::PieceIcon(const std::string color, QWidget* parent) :
	QPushButton(parent), piece_(ChessModel::Board::pieceNotFound),color_(color)
{
	setMinimumSize(PIECEICONSIZE);
	update(piece_);
}

void PieceIcon::update(ChessModel::PiecePtr piece)
{
	piece_ = piece;

	QString image = QString::fromStdString((piece_ != ChessModel::Board::pieceNotFound)
		? "border-image: url( './Images/Pieces/" +
		static_cast<std::string>(typeid(*piece_).name()).substr(static_cast<std::string>(typeid(*piece_).name()).find_last_of(':') + 1) +
		"_" + piece_->getColor() + ".png') 0 0 0 0 stretch stretch;"
		: WHITEBACKGROUND);
	setStyleSheet(image);

}

ChessModel::PiecePtr PieceIcon::getPiece() const
{
	return piece_;
}
