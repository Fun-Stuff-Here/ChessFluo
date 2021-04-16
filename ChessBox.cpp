/*
* Implémentation de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/

#include "ChessBox.h"
#include "Constant.h"
#include "ChessFluoWindow.h"
#include <string>
#include <algorithm>
#include <typeinfo>
#include <iostream>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>

using namespace ChessView;

ChessBox::ChessBox(BoardPtr& board, ChessModel::Position& position,ChessFluoWindow* boardView, QWidget* parent)
	:QPushButton(parent), position_(position),boardView_(boardView)
{
	board_ = board;
	piece_ = board_->getPiece(position_);
	setMinimumSize(CHESSBOXSIZE);
	QString style = (position.first + position.second) % 2 == 0 ? "background-color: DarkMagenta;" : "background-color: Coral;";
	QString image = QString::fromStdString((piece_ != ChessModel::Board::pieceNotFound)
		? "border-image: url( './Images/Pieces/" +
		static_cast<std::string>(typeid(*piece_).name()).substr(static_cast<std::string>(typeid(*piece_).name()).find_last_of(':') + 1) +
		"_" + piece_->getColor() + ".png') 0 0 0 0 stretch stretch;"
		:"");

	setStyleSheet(style+image);

	auto opacitySelected = new QGraphicsOpacityEffect();
	opacitySelected->setOpacity(1);
	setGraphicsEffect(opacitySelected);

	connect(this,SIGNAL(clicked()),
	this, SLOT(selected(void)));
}


void ChessBox::selected()
{
	std::cout << "chessbox selected " << position_.first << "," << position_.second << std::endl;
	if (piece_)
	{
		boardView_->selections(piece_);
	}
}
