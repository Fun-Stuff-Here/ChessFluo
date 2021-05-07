/*
* Définition de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967 
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma pop()

#include "Board.h"
#include "ChessBox.h"
#include"BoardView.h"
#include"PositionView.h"
#include "FeaturesView.h"
#include "EatView.h"
#include "Turn.h"


namespace ChessView
{
	
	

	class ChessFluoWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		ChessFluoWindow(QWidget* parent = nullptr);
		~ChessFluoWindow() override = default;
		BoardView* getBoardView();


	public slots:


	private:
		ChessModel::GamePtr game_;
		BoardView boardview_;
		PositionView positionView_;
		FeaturesView featuresView_;
		EatView eatView_;
		Turn turnView_;

		void connectMenu();

	};
}



