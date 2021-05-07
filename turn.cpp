/*
* Implémentation de la Classe Turn, Projet-INF1015
*\file		Turn.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		7 mai 2021
* Créé le	7 mai 2021
*/
#include "Turn.h"
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

Turn::Turn(ChessModel::GamePtr game, QWidget* parent):
	QWidget(parent),game_(game),icon_(game,this)
{

	QGridLayout* topLayout = new QGridLayout(this);


	QLabel* tourLabel = new QLabel(this);
	tourLabel->setText("Tour : ");
	topLayout->addWidget(tourLabel,0,0);

	topLayout->addWidget(&icon_, 0, 1);

	setLayout(topLayout);
	setFixedSize(topLayout->totalMinimumSize());
}


void Turn::update()
{
	icon_.update();
}