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

	using Position = std::pair<int, int>;
	const std::vector<Position> CASTLINGPOSITIONS = {
	{7,1},
	{3,1},
	{7,8},
	{3,8}
	};
	const std::vector<Position> SMALLCASTLINGPOSITIONS = {
	{7,1},
	{7,8},
	};
	const std::vector<Position> BIGCASTLINGPOSITION = {
	{3,1},
	{3,8}
	};


}


namespace ChessView
{
	const QSize CHESSBOXSIZE{ 50, 50 };
	const unsigned int NROWS{ 8 };
	const unsigned int  NCOLUMNS{ 8 };
	const double SELECTIONOPACITY{ 0.5 };
	const double FULLOPACITY{ 1.0 };
	const QString TILECOLOR1 = "background-color: DarkMagenta;";
	const QString TILECOLOR2 = "background-color: Coral;";
}