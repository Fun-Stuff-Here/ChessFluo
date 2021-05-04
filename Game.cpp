/*
* Implémentation de la Classe Game, Projet-INF1015
*\file		Game.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/

#include "Game.h"
#include "King.h"
#include "exeptions.h"

using namespace ChessModel;

bool Game::isCheckable(Position&& position, const std::string& color)
{
	for (auto&& [positionKey, piece] : board_.getPieces())
	{
		auto king = dynamic_cast<King*>(piece.get());
		if (king || piece->getColor() == color)
			continue;

		auto moves = piece->getMoves();
		auto positionOfPieceCheck = std::find_if(moves.begin(), moves.end(),
			[&position](Position positionParam)->bool {return position == positionParam; });

		if (positionOfPieceCheck != moves.end())
			return true;
	}
	return false;
}

bool Game::isCheckable(Position& position, const std::string& color)
{
	return isCheckable(position, color);
}


void Game::verifieCheck(const std::string& color)
{
	auto pieces = board_.getPieces();
	auto king = std::find_if(pieces.begin(), pieces.end(),
		[&color](auto it)->bool {return color == it.second->getColor() && dynamic_cast<King*>(it.second.get()); });
	if (king == pieces.end())
		throw NotTwoKings("Required two kings to move");

	auto kingPosition = king->first;

	if (isCheckable(kingPosition, color))
	{
		throw Check(color);
	}

}



bool Game::isEnded()
{
	throw NotImplemented();
}

bool Game::isCheckMate()
{
	throw NotImplemented();
}