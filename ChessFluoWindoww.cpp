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
#include "exeptions.h"

using namespace ChessView;

ChessFluoWindow::ChessFluoWindow(QWidget* parent):
	QMainWindow(parent)
{

	QWidget* mainWidget = new QWidget(this);
	QGridLayout*mainGridLayout = new QGridLayout(this);

	//TOP PART
	QWidget* topWidget = new QWidget(mainWidget);
	QHBoxLayout* topLayout = new QHBoxLayout(mainWidget);

	QLabel* tourLabel = new QLabel(topWidget);
	tourLabel->setText("Tour : ");
	topLayout->addWidget(tourLabel);

	QLabel* timeLabel = new QLabel(topWidget);
	timeLabel->setText("Temps : ");
	topLayout->addWidget(timeLabel);

	topWidget->setLayout(topLayout);
	mainGridLayout->addWidget(topWidget, 0, 0);

	//GAME MODE PART
	QWidget* gamemodeWidget = new QWidget(mainWidget);
	QVBoxLayout* gamemodeLayout = new QVBoxLayout(mainWidget);

	QLabel* gamemodeLabel = new QLabel(gamemodeWidget);
	gamemodeLabel->setText("Mode de jeu :");
	gamemodeLayout->addWidget(gamemodeLabel);

	gamemodeWidget->setLayout(gamemodeLayout);
	mainGridLayout->addWidget(gamemodeWidget, 0, 1);

	//BOARD PART
	boardview_.setParent(mainWidget);
	mainGridLayout->addWidget(&boardview_,1,0);

	//POSITIONS PART
	positionView_.setParent(mainWidget);
 	mainGridLayout->addWidget(&positionView_, 1, 2);


	//EATEN PIECES PART
	QWidget* middleWidget = new QWidget(mainWidget);
	QVBoxLayout* middleLayout = new QVBoxLayout(mainWidget);

	QLabel* eatenPiecesLabel = new QLabel(middleWidget);
	eatenPiecesLabel->setText("Pièces mangées : ");
	eatenPiecesLabel->setAlignment(Qt::AlignTop);
	eatenPiecesLabel->setAlignment(Qt::AlignLeft);
	middleLayout->addWidget(eatenPiecesLabel);

	middleWidget->setLayout(middleLayout);
	mainGridLayout->addWidget(middleWidget, 1, 1);

	//BOTTOM PART
	QWidget* bottomWidget = new QWidget(mainWidget);
	QHBoxLayout* bottomLayout = new QHBoxLayout(mainWidget);

	QPushButton* startBtn = new QPushButton(mainWidget);
	startBtn->setText("Start");
	bottomLayout->addWidget(startBtn);

	QPushButton* undoBtn = new QPushButton(mainWidget);
	undoBtn->setText("Undo");
	bottomLayout->addWidget(undoBtn);

	QPushButton* redoBtn = new QPushButton(mainWidget);
	redoBtn->setText("Redo");
	bottomLayout->addWidget(redoBtn);

	bottomWidget->setLayout(bottomLayout);
	mainGridLayout->addWidget(bottomWidget, 2, 0);

	mainWidget->setMinimumSize((NROWS+6) * CHESSBOXSIZE);
	mainWidget->setLayout(mainGridLayout);
	
}
