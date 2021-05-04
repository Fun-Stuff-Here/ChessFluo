/*
* Implémentation des Classes reli/ aux Players, Projet-INF1015
*\file		Players.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/

#include "Players.h"

using namespace ChessModel;

Player::Player(std::string& color):
	color_(color){}



std::string Player::getColor() const
{
	return color_;
}