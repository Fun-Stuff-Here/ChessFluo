/*
* Implémentation de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967 
*\date		13 avril 2021
* Créé le	13 avril 2021
*/




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

#include <iostream>

#include "ChessBox.h"
#include "Constant.h"
#include "ChessFluoWindow.h"
#include "Turn.h"
#include "exeptions.h"

using namespace ChessView;

ChessFluoWindow::ChessFluoWindow(QWidget* parent):
	QMainWindow(parent),game_(std::make_shared<ChessModel::Game>()),
	boardview_(game_), positionView_(game_), featuresView_(game_), eatView_(game_), turnView_(game_)
{

	QWidget* mainWidget = new QWidget(this);
	QGridLayout*mainGridLayout = new QGridLayout(this);


	turnView_.setParent(mainWidget);
	mainGridLayout->addWidget(&turnView_, 0, 0);


	//BOARD PART
	boardview_.setParent(mainWidget);
	mainGridLayout->addWidget(&boardview_,1,0);

	//POSITIONS PART
	positionView_.setParent(mainWidget);
 	mainGridLayout->addWidget(&positionView_, 1, 2);


	//EATEN PIECES PART
	eatView_.setParent(mainWidget);
	mainGridLayout->addWidget(&eatView_, 1, 1);

	//BOTTOM PART
	featuresView_.setParent(mainWidget);
	mainGridLayout->addWidget(&featuresView_, 2, 0);


	
	mainWidget->setMinimumSize(mainGridLayout->totalMinimumSize());
	mainWidget->setLayout(mainGridLayout);

	connectMenu();


}


BoardView* ChessFluoWindow::getBoardView()
{
	return &boardview_;
}


void ChessFluoWindow::connectMenu()
{
	connect(&positionView_, SIGNAL(updateBoard(void)), &boardview_, SLOT(update(void)));
	connect(&featuresView_, SIGNAL(updateBoard(void)), &boardview_, SLOT(update(void)));
	connect(&boardview_, SIGNAL(eatViewUpdate(void)), &eatView_, SLOT(update(void)));
	connect(&boardview_, SIGNAL(turnViewUpdate(void)), &turnView_, SLOT(update(void)));
}