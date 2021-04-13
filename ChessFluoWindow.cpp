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

using namespace ChessView;

ChessFluoWindow::ChessFluoWindow(QWidget* parent):
	QMainWindow(parent)
{
	auto mainWidget = new QWidget(this);
	auto mainLayout = new QGridLayout(mainWidget);

	//auto case11 = new ChessBox(mainWidget);
	//auto case12 = new ChessBox(mainWidget);

	//auto label1 = new QLabel(mainWidget);
	//auto label2 = new QLabel(mainWidget);
	//label1->setText("label 1");
	//label2->setText("label 2");

	//label1->setMinimumWidth(100);
	//label2->setMinimumWidth(100);

	//mainLayout->addWidget(case11);//, 2, 2, Qt::AlignHCenter, Qt::AlignHCenter);
	//mainLayout->addSpacing(10);
	//mainLayout->addWidget(case12);//, 1, 1, Qt::AlignHCenter, Qt::AlignHCenter);
	//mainLayout->addSpacing(10);
	//mainLayout->addWidget(label1);//, 0, 0, Qt::AlignHCenter, Qt::AlignHCenter);
	//mainLayout->addSpacing(10);
	//mainLayout->addWidget(label2);//, 3, 3, Qt::AlignHCenter, Qt::AlignHCenter);
	QPushButton* button1 = new QPushButton("One");
	QPushButton* button2 = new QPushButton("Two");
	QPushButton* button3 = new QPushButton("Three");
	QPushButton* button4 = new QPushButton("Four");
	QPushButton* button5 = new QPushButton("Five");

	//QGridLayout* layout = new QGridLayout(mainWidget);
	mainLayout->addWidget(button1, 0, 0);
	mainLayout->addWidget(button2, 0, 1);
	mainLayout->addWidget(button3, 1, 0, 1, 2);
	mainLayout->addWidget(button4, 2, 0);
	mainLayout->addWidget(button5, 2, 1);

}



