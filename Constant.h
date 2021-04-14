/*
* Définition des constantes, Projet-INF1015
*\file		Constant.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <qsize.h>
#include <QLabel>
#include <QString>
#pragma pop()

#include <string>

namespace ChessModel {

	const std::string COLORPLAYER1 = "bluelaite";
	const std::string COLORPLAYER2 = "vertmoisi";
	const unsigned int NROWS{ 8 };
	const unsigned int  NCOLUMNS{ 8 };
}


namespace ChessView
{
	const QSize CHESSBOXSIZE{ 150, 150 };
	const unsigned int NROWS{ 8 };
	const unsigned int  NCOLUMNS{ 8 };
}