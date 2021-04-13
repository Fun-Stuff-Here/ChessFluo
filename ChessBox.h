/*
* Définition de la Classe ChessBox, Projet-INF1015
*\file		ChessBox.hpp
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
#include <qgroupbox.h>
#pragma pop()

#include <memory>

class ChessBox: public QWidget
{
public:
	ChessBox(QWidget* parent = nullptr);
	~ChessBox()=default;

private:

	std::shared_ptr<QLabel> label_;
};
