/*
* Implémentation de la Classe TurnIcon, Projet-INF1015
*\file		TurnIcon.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		7 mai 2021
* Créé le	7 mai 2021
*/
#include "TurnIcon.h"
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

TurnIcon::TurnIcon(ChessModel::GamePtr game, QWidget* parent):
	QPushButton(parent), game_(game)
{
	setMinimumSize(TURNTILE);
	update();
}


void TurnIcon::update()
{
	auto turn = game_->getTurn();

	QString colorStyle = (turn == ChessModel::COLORPLAYER1) ? QWHITEBACKGROUND : QBLACKBACKGROUND;
	setStyleSheet(colorStyle);
}