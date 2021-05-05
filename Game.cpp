/*
* Impl�mentation de la Classe Game, Projet-INF1015
*\file		Game.cpp
*\author	Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Cr�� le	13 avril 2021
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





PiecePtr Game::move(PiecePtr& piece, Position&& position)
{
	return move(piece, position);
}

PiecePtr Game::move(PiecePtr& piece, Position& position)
{
	auto positionPiece = piece->getPosition();
	if (!isValidMove(positionPiece,position)) throw ImpossibleMove();
	auto move = moveTry(piece, position);
	moveHistory_.push_back(move);
	piece->setPosition(position);
	turn_ = board_.getOpponentColor(turn_);
	//castling conditions updating
	auto rook = dynamic_cast<Rook*>(piece.get());
	auto king = dynamic_cast<King*>(piece.get());
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
	verifieCheck(board_.getOpponentColor(piece->getColor()));
	return move->getPieceEat();
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


	if (turn_ != piece->getColor()) throw ImpossibleMove();
	
	move->execute(this);

	verifieCheck(piece->getColor());

	return move;
}

bool Game::isValidMove(Position& from, Position& to)
{
	auto validPositions = getMovesPositions(from);
	auto it = std::find(validPositions.begin(), validPositions.end(), to);
	return it != validPositions.end();
}


std::vector<Position> Game::getMovesPositions(Position&& position)
{
	return getMovesPositions(position);
}

std::vector<Position> Game::getMovesPositions(Position& position) 
{
	std::vector<Position> positions{};
	auto piece = board_.getPiece(position);

	if (piece == Board::pieceNotFound) return positions;
	if (piece->getColor() != turn_) return positions;

	positions = piece->getMoves();


	//filter thoses who puts king in check
	std::vector<Position> filteredPositions{};
	std::copy_if(positions.begin(),positions.end(),std::back_inserter(filteredPositions), 
		[&piece, this](Position position) -> bool {
			bool toRemove = false;
			auto save = board_.save();
			try
			{
				this->moveTry(piece, position);
			}
			catch (const ImpossibleMove&)
			{
				toRemove = true;
			}
			catch (const Check&)
			{
				toRemove = true;
			}
			catch (const Promotion&) {}

			board_.restore(save);
			return !toRemove;
		}
		);

	return filteredPositions;
}

Board* Game::getBoard()
{
	return &board_;
}