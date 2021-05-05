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

	boardview_.setParent(mainWidget);
	mainGridLayout->addWidget(&boardview_,0,0);

	//Qobject::connect(&c1, SIGNAL(valueChanged(int)),
	//	&c2, SLOT(setValue(int)));

	

	QLabel* label = new QLabel(mainWidget);
	label->setText("Tour : ");
	mainGridLayout->addWidget(label,0,1);



	mainWidget->setMinimumSize((NROWS+5) * CHESSBOXSIZE);
	mainWidget->setLayout(mainGridLayout);
	
	//QWidget* mainWidget = new QWidget(this);
	//QHBoxLayout* mainHLayout = new QHBoxLayout(mainWidget);
	//mainWidget->setLayout(mainHLayout);



	//QLabel* label = new QLabel(this);
	//label->setText("Tour : ");
	//mainHLayout->addWidget(label);

	//QLabel* label2 = new QLabel(this);
	//label2->setText("TOUR : ");
	//mainHLayout->addWidget(label);


}
