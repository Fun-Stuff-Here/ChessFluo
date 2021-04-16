/*
* Implémentation de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967 
*\date		13 avril 2021
* Créé le	13 avril 2021
*/

#include "ChessFluoWindow.h"


#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <qgridlayout.h>
#pragma pop()

#include "ChessBox.h"
#include "Constant.h"

using namespace ChessView;

ChessFluoWindow::ChessFluoWindow(QWidget* parent):
	QMainWindow(parent)
{
	board_ = std::make_shared<ChessModel::Board>();

	auto mainWidget = new QWidget(this);
	QGridLayout *mainGridLayout = new QGridLayout(mainWidget);
	
	for (int i = 0; i < NROWS; ++i)
	{
		for (size_t j = 0; j < NCOLUMNS; j++)
		{
			ChessModel::Position position{j+1,i+1};
			auto chessBox = new ChessBox{board_,position,mainWidget};
			mainGridLayout->addWidget(chessBox, i, j);
			mainGridLayout->setSpacing(0);
		}
	}
	mainWidget->setLayout(mainGridLayout);
	mainWidget->setMinimumSize(NROWS * CHESSBOXSIZE);

}



