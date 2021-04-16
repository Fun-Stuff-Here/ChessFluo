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
#pragma pop()

#include <iostream>

#include "ChessBox.h"
#include "Constant.h"
#include "ChessFluoWindow.h"

using namespace ChessView;

ChessFluoWindow::ChessFluoWindow(QWidget* parent):
	QMainWindow(parent)
{
	board_ = std::make_shared<ChessModel::Board>();
	selectedPiece_ = ChessModel::Board::pieceNotFound;

	auto mainWidget = new QWidget(this);
	QGridLayout *mainGridLayout = new QGridLayout(mainWidget);
	
	for (int i = 0; i < NROWS; ++i)
	{
		for (size_t j = 0; j < NCOLUMNS; j++)
		{
			ChessModel::Position position{j+1,i+1};
			ChessBoxPtr chessBox = std::make_shared<ChessBox>(board_, position ,this,mainWidget);
			chessBoxes_[position] = chessBox;
			mainGridLayout->addWidget(chessBox.get(),NROWS- i, j);
			mainGridLayout->setSpacing(0);
		}
	}
	//Qobject::connect(&c1, SIGNAL(valueChanged(int)),
	//	&c2, SLOT(setValue(int)));

	
	mainWidget->setLayout(mainGridLayout);
	mainWidget->setMinimumSize(NROWS * CHESSBOXSIZE);
}

void ChessFluoWindow::selections(ChessModel::PiecePtr& piece)
{
	if(selectedPiece_)
	{
		auto effect = dynamic_cast<QGraphicsOpacityEffect*>(chessBoxes_[selectedPiece_->getPosition()]->graphicsEffect());
		effect->setOpacity(1);

		for(auto&& position: selectedPiece_->getMoves())
		{
			effect = dynamic_cast<QGraphicsOpacityEffect*>(chessBoxes_[position]->graphicsEffect());
			effect->setOpacity(1);
		}
	}
	if(selectedPiece_ != piece)
	{
		https://forum.qt.io/topic/74101/two-graphicseffects-for-one-qwidget
		auto effect = dynamic_cast<QGraphicsOpacityEffect*>(chessBoxes_[piece->getPosition()]->graphicsEffect());
		effect->setOpacity(SELECTIONOPACITY);
	
		for(auto&& position: piece->getMoves())
		{
			std::cout << position.first << ", " << position.second << std::endl;
			auto effect = dynamic_cast<QGraphicsOpacityEffect*>(chessBoxes_[position]->graphicsEffect());
			effect->setOpacity(SELECTIONOPACITY);
		}
	}
	selectedPiece_ =  (selectedPiece_ == piece) ? ChessModel::Board::pieceNotFound : piece;

}


