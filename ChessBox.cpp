/*
* Impl�mentation de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.cpp
*\author	Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Cr�� le	13 avril 2021
*/

#include "ChessBox.h"


ChessBox::ChessBox(QWidget* parent )
	:QWidget(parent)
{

	rect();
	label_ = std::make_shared<QLabel>();
	label_->setText("case icittteeee");

}