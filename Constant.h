/*
* D�finition des constantes, Projet-INF1015
*\file		Constant.hpp
*\author	Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544
*\date		12 avril 2021
* Cr�� le	10 avril 2021
*/
#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
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
	const int NROWS{ 8 };
	const int  NCOLUMNS{ 8 };
	const double SELECTIONOPACITY{ 0.5 };
	const double FULLOPACITY{ 1.0 };
	const QString TILECOLOR1 = "background-color: DarkMagenta;";
	const QString TILECOLOR2 = "background-color: Coral;";
	const std::string WHITEBACKGROUND = "border-image: url( './Images/White.png') 0 0 0 0 stretch stretch;";
	const std::string BLACKBACKGROUND = "border-image: url( './Images/black.png') 0 0 0 0 stretch stretch;";
	const QString QBLACKBACKGROUND = "border-image: url( './Images/BlackTurn.png') 0 0 0 0 stretch stretch;";
	const QString QWHITEBACKGROUND = "border-image: url( './Images/WhiteTurn.png') 0 0 0 0 stretch stretch;";
	const QSize PIECEICONSIZE{ 25, 25 };
	const QSize TURNTILE{ 35, 35 };
	const int NPLAYER = 2;
	const QString IMPOSSIBLEMOVESOUNDPATH = "/Sounds/ImposssibleMove.wav";


}