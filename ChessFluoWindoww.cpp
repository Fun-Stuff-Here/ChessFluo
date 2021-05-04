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
	QMainWindow(parent),boardview_(this)
{
	

	QWidget* mainWidget = new QWidget(this);
	QGridLayout*mainGridLayout = new QGridLayout(mainWidget);
	
	mainGridLayout->addWidget(&boardview_);
	//Qobject::connect(&c1, SIGNAL(valueChanged(int)),
	//	&c2, SLOT(setValue(int)));

	
	mainWidget->setLayout(mainGridLayout);
	mainWidget->setMinimumSize((NROWS+1) * CHESSBOXSIZE);
}

