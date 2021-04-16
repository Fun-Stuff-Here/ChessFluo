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

using namespace ChessView;

ChessBox::ChessBox(BoardPtr& board, ChessModel::Position position, QWidget* parent)
	:QPushButton(parent), board_(board), position_(position)
{
	piece_ = board_->getPiece(position_);
	setMinimumSize(CHESSBOXSIZE);
	QString style = (position.first + position.second) % 2 == 0 ? "background-color: Chartreuse;" : "background-color: Coral;";
	QString image = QString::fromStdString((piece_ != ChessModel::Board::pieceNotFound)
		? "border-image: url( './Images/Pieces/" +
		static_cast<std::string>(typeid(*piece_).name()).substr(static_cast<std::string>(typeid(*piece_).name()).find_last_of(':') + 1) +
		"_" + piece_->getColor() + ".png') 0 0 0 0 stretch stretch;"
		:"");

	setStyleSheet(style+image);
}
