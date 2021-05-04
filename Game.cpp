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
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"


using namespace ChessModel;

Game::Game():
	board_(),moveHistory_()
{
	turn_ = COLORPLAYER1;
}



void Game::verifieCheck(const std::string& color)
{
	auto pieces = board_.getPieces();
	auto king = std::find_if(pieces.begin(), pieces.end(),
		[&color](auto it)->bool {return color == it.second->getColor() && dynamic_cast<King*>(it.second.get()); });
	if (king == pieces.end())
		throw NotTwoKings("Required two kings to move");

	auto kingPosition = king->first;

	if (board_.isCheckable(kingPosition, color))
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





void Game::move(PiecePtr& piece, Position&& position)
{
	return move(piece, position);
}

void Game::move(PiecePtr& piece, Position& position)
{
	if (!isValidMove(position)) throw ImpossibleMove();
	moveHistory_.push_back(moveTry(piece, position));
	piece->setPosition(position);
	verifieCheck(piece->getColor());
}


MovePtr Game::moveTry(PiecePtr& piece, Position& position)
{
	MovePtr move = nullptr;

	auto from = piece->getPosition();
	auto pieces = board_.getPieces();

	auto pawn = dynamic_cast<Pawn*>(piece.get());
	if (pawn && (position.second == 0 || position.second == NROWS)) 
		move = static_cast<MovePtr>(new PromotionMove{pieces,from ,position });
	

	auto king = dynamic_cast<King*>(piece.get());
	auto castlingPosition =  std::find(CASTLINGPOSITIONS.begin(), CASTLINGPOSITIONS.end(),position);
	if (king && castlingPosition != CASTLINGPOSITIONS.end())
		move = static_cast<MovePtr>(new CastlingMove{ pieces,from,position });

	if (!move) move = static_cast<MovePtr>(new RegularMove{pieces,from,position});

	//castling conditions updating
	auto rook = dynamic_cast<Rook*>(piece.get());
	if (king)
		king->moved();
	if (rook)
	{
		if (rook->getPosition() == Position{ 1,1 })
			board_.getKing(COLORPLAYER1)->bigCastlingRookMoved();
		if (rook->getPosition() == Position{ 8,1 })
			board_.getKing(COLORPLAYER1)->smallCastlingRookMoved();
		if (rook->getPosition() == Position{ 8,8 })
			board_.getKing(COLORPLAYER2)->smallCastlingRookMoved();
		if (rook->getPosition() == Position{ 1,8 })
			board_.getKing(COLORPLAYER2)->bigCastlingRookMoved();
	}



	if (turn_ != piece->getColor()) throw ImpossibleMove();
	
	move->execute(this);

	turn_ = board_.getOpponentColor(turn_);

	return move;
}

bool Game::isValidMove(Position& position)
{
	auto validPositions = getMovesPositions(position);
	auto it = std::find(validPositions.begin(), validPositions.end(), position);
	return it != validPositions.end();
}

std::vector<Position> Game::getMovesPositions(Position& position) 
{
	std::vector<Position> positions{};
	auto piece = board_.getPiece(position);

	if (piece == Board::pieceNotFound) return positions;
	if (piece->getColor() != turn_) return positions;

	positions = piece->getMoves();

	//filter thoses who puts king in check
	std::vector<std::vector<Position>::iterator> toRemoves;
	for (auto it = positions.begin(); it != positions.end(); it++)
	{
		auto save = board_.save();
		try
		{
			 moveTry(piece, *it);
		}
		catch (const ImpossibleMove&)
		{
			toRemoves.push_back(it);
		}
		catch(const Check&) {}
		catch(const Promotion&){}

		board_.restore(save);
	}

	for (auto&& toRemove : toRemoves)
		positions.erase(toRemove);


	return positions;
}

Board* Game::getBoard()
{
	return &board_;
}