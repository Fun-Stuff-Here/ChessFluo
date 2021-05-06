/*
* Implémentation de la Classe BoardView, Projet-INF1015
*\file		BoardView.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#include "FeaturesView.h"
#include "exeptions.h"
#include "Game.h"
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

FeaturesView::FeaturesView(ChessModel::GamePtr& game, QWidget* parent) :
	QWidget(parent), game_(game)
{
	QHBoxLayout* bottomLayout = new QHBoxLayout(this);

	QPushButton* startBtn = new QPushButton(this);
	startBtn->setText("Start");
	bottomLayout->addWidget(startBtn);
	connect(startBtn, SIGNAL(clicked()), this, SLOT(regularStart(void)));

	QPushButton* undoBtn = new QPushButton(this);
	undoBtn->setText("Undo");
	bottomLayout->addWidget(undoBtn);
	connect(undoBtn, SIGNAL(clicked()), this, SLOT(undo(void)));

	QPushButton* redoBtn = new QPushButton(this);
	redoBtn->setText("Redo");
	bottomLayout->addWidget(redoBtn);
	connect(redoBtn, SIGNAL(clicked()), this, SLOT(redo(void)));

	QPushButton* resetBtn = new QPushButton(this);
	resetBtn->setText("Reset");
	bottomLayout->addWidget(resetBtn);
	connect(resetBtn, SIGNAL(clicked()), this, SLOT(reset(void)));

	setLayout(bottomLayout);
}


void FeaturesView::start()
{
	//game_->start(ChessModel::Regular2PlayerGame{});
	//boardView_.update();
	//emit();
}
void FeaturesView::undo()
{
	//game_->undo();
	//emit();
}
void FeaturesView::redo()
{
	//game_->redo();
	//emit();
}

void FeaturesView::reset()
{
	//à faire
}
