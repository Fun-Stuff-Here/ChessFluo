/*
* D�finition de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.hpp
*\author	Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544, Afaf Djellabi 2089967 
*\date		13 avril 2021
* Cr�� le	13 avril 2021
*/
#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma pop()

#include "Board.h"

namespace ChessView
{
	class ChessFluoWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		ChessFluoWindow(QWidget* parent = nullptr);
		~ChessFluoWindow() override = default;

	public slots:



	private:
		//template <typename T = decltype(nullptr)>
		//QPushButton* nouveauBouton(const QString & text, const T & slot = nullptr);

		ChessModel::Board board_;  // Le Mod�le (pourrait �tre un pointeur mais pas n�cessaire dans ce cas).

	};
}



