/*
* Implémentation de la Classe BoardView, Projet-INF1015
*\file		BoardView.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#include "PositionView.h"
#include "exeptions.h"

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

PositionView::PositionView(ChessModel::GamePtr& game, QWidget* parent) :
	QWidget(parent),game_(game)
{
	QVBoxLayout* positionLayout = new QVBoxLayout(this);

	QLabel* positionChoices = new QLabel(this);
	positionChoices->setText("Choix de positions : ");
	positionChoices->setAlignment(Qt::AlignTop);
	positionLayout->addWidget(positionChoices);

	QPushButton* regularPositionsBtn = new QPushButton(this);
	regularPositionsBtn->setText("Positions régulières");
	positionLayout->addWidget(regularPositionsBtn);
	connect(regularPositionsBtn,SIGNAL(clicked()),this, SLOT(regularStart(void)));

	QPushButton* puzzle1PositionsBtn = new QPushButton(this);
	puzzle1PositionsBtn->setText("Puzzle 1");
	positionLayout->addWidget(puzzle1PositionsBtn);
	connect(puzzle1PositionsBtn,SIGNAL(clicked()),this, SLOT(puzzle1(void)));

	QPushButton* puzzle2PositionsBtn = new QPushButton(this);
	puzzle2PositionsBtn->setText("Puzzle 2");
	positionLayout->addWidget(puzzle2PositionsBtn);
	connect(puzzle2PositionsBtn, SIGNAL(clicked()), this, SLOT(puzzle2(void)));

	QPushButton* puzzle3PositionsBtn = new QPushButton(this);
	puzzle3PositionsBtn->setText("Puzzle 3");
	positionLayout->addWidget(puzzle3PositionsBtn);
	connect(puzzle3PositionsBtn,SIGNAL(clicked()),this, SLOT(puzzle3(void)));

	QPushButton* puzzle4PositionsBtn = new QPushButton(this);
	puzzle4PositionsBtn->setText("Puzzle 4");
	positionLayout->addWidget(puzzle4PositionsBtn);
	connect(puzzle4PositionsBtn,SIGNAL(clicked()),this, SLOT(puzzle4(void)));

	setLayout(positionLayout);
}


void PositionView::regularStart()
{
	game_->start(ChessModel::Regular2PlayerGame{});
	Q_EMIT updateBoard();
}
void PositionView::puzzle1()
{
	game_->start(ChessModel::WhiteToCheckMate1{});
	Q_EMIT updateBoard();
}
void PositionView::puzzle2()
{
	game_->start(ChessModel::WhiteToCheckMate2{});
	Q_EMIT updateBoard();
}
void PositionView::puzzle3()
{
	game_->start(ChessModel::WhiteToWin1{});
	Q_EMIT updateBoard();
}
void PositionView::puzzle4()
{
	game_->start(ChessModel::WhiteToWin2{});
	Q_EMIT updateBoard();
}