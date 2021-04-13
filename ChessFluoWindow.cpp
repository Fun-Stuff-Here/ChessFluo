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
	QGridLayout *mainGridLayout = new QGridLayout(mainWidget);
	//auto layout = new QHBoxLayout();
	//mainLayout->addLayout(layout);
	const QSize buttonSize = QSize(150, 150);
	QString name = "allo";
	
	for (int i = 0; i < 8; ++i)
	{
		for (size_t j = 0; j < 8; j++)
		{
			auto button = new QPushButton(mainWidget);
			button->setText(name);
			button->setMinimumSize(buttonSize);
			QString style = (j+i) % 2 == 0 ? "background-color: black;" : "background-color: white; border: 2px solid black;";
			button->setStyleSheet(style);
			mainGridLayout->addWidget(button, i, j);
			mainGridLayout->setSpacing(0);
		}
	}
	mainWidget->setLayout(mainGridLayout);
	const QSize mainSize{ 8 * 150, 8 * 150 };
	mainWidget->setMinimumSize(mainSize);

}



