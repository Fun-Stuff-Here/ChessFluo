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
	const QSize btnSize = QSize(2500, 1500);
	QString name = "allo";
	for (int i = 0; i < 3; ++i)
	{
		auto button = new QPushButton(mainWidget);
		button->setText(name);
		button->setFixedSize(btnSize);
		mainGridLayout->addWidget(button, 0, i);
		mainGridLayout->setSpacing(0);
	}
	mainWidget->setLayout(mainGridLayout);

}



