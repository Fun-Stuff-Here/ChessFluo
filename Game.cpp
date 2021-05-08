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
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"


using namespace ChessModel;

Game::Game():
	board_(Empty{}), moveHistory_()
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
	return isFinished_;
}

bool Game::isCheckMate(const std::string& color)
{
	if (getAllMovesPositions(color).size() == 0)
	{
		isFinished_ = true;
		return true;
	}
	return false;
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
	auto pieceEat = move->getPieceEat();
	if (pieceEat)
		piecesEat_.insert(pieceEat);
	piece->setPosition(position);
	changeTurn();
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
	redoClear();
	try
	{
		verifieCheck(board_.getOpponentColor(piece->getColor()));
	}
	catch (const Check&)
	{
		if (isCheckMate(turn_))
			throw CheckMate("CheckMate on "+ turn_);
		throw;
	}
	return move->getPieceEat();
}


MovePtr Game::moveTry(PiecePtr& piece, Position& position)
{
	MovePtr move = nullptr;

	auto from = piece->getPosition();
	auto pieces = board_.getPieces();

	auto pawn = dynamic_cast<Pawn*>(piece.get());
	if (pawn && (position.second == 1 || position.second == NROWS)) 
		move = static_cast<MovePtr>(new PromotionMove{pieces,from ,position });
	

	auto king = dynamic_cast<King*>(piece.get());
	auto castlingPosition =  std::find(CASTLINGPOSITIONS.begin(), CASTLINGPOSITIONS.end(),position);
	if (king && castlingPosition != CASTLINGPOSITIONS.end())
	{
		if(king->canBigCastle() && std::find(BIGCASTLINGPOSITION.begin(), BIGCASTLINGPOSITION.end(), position) != BIGCASTLINGPOSITION.end())
			move = static_cast<MovePtr>(new CastlingMove{ pieces,from,position });
		if (king->canSmallCastle() && std::find(SMALLCASTLINGPOSITIONS.begin(), SMALLCASTLINGPOSITIONS.end(), position) != SMALLCASTLINGPOSITIONS.end())
			move = static_cast<MovePtr>(new CastlingMove{ pieces,from,position });
	}
		

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
			board_.restore(save);
			return !toRemove;
		}
		);
		
	if (dynamic_cast<King*>(piece.get()))
	{
		std::vector<Position> kingFilterPosition{};
		std::copy_if(filteredPositions.begin(), filteredPositions.end(), std::back_inserter(kingFilterPosition),
			[&piece, this](Position position) -> bool {
				bool toRemove = false;
				auto oppositeKing = board_.getKing(board_.getOpponentColor(piece->getColor()));

				auto oppositeKingMoves = oppositeKing->getMovesFromOffsets();
				if (std::find(oppositeKingMoves.begin(), oppositeKingMoves.end(), position) != oppositeKingMoves.end())
					toRemove = true;
				return !toRemove;
			}
		);
		return kingFilterPosition;
	}




	return filteredPositions;
}

Board* Game::getBoard()
{
	return &board_;
}


std::string Game::getTurn() const
{
	return turn_;
}


std::vector<MovePtr> Game::getAllMovesPositions(const std::string& color)
{
	std::vector<MovePtr> moves{};
	auto pieces = board_.getPieces();
	for (auto&& it:pieces)
	{
		if (it.second->getColor() != color) continue;
		auto piecePosition = it.second->getPosition();
		for (auto&& position : getMovesPositions(const_cast<Position&>(it.first)))
		{
			MovePtr movePiece{new RegularMove{ pieces,piecePosition,position }};
			moves.emplace_back(movePiece);
		}
		
	}

	return moves;

}






void Game::start()
{
	isFinished_ = false;
	turn_ = COLORPLAYER1;
	board_.clearPieces();
	moveHistory_.clear();
	redoHistory_.clear();
	piecesEat_.clear();
}


void Game::start(Regular2PlayerGame)
{
	start();
	board_.fill();

}

void Game::start(Regular1PlayerGame)
{
	start();
	board_.fill();
}

void Game::start(WhiteToCheckMate1)
{
	//Magnus - Harestad 25th Politiken Cup
	start();
	board_.fill(WhiteToCheckMate1{});
	board_.getKing(COLORPLAYER1)->moved();
	board_.getKing(COLORPLAYER2)->moved();
}


void Game::start(WhiteToCheckMate2)
{
	//Kasparov - Ivanchuk 55th URS-ch
	start();
	board_.fill(WhiteToCheckMate2{});
	board_.getKing(COLORPLAYER1)->moved();
	board_.getKing(COLORPLAYER2)->moved();

}


void Game::start(WhiteToWin1)
{
	//Pollack - Mulay London classic open 2016
	start();
	board_.fill(WhiteToWin1{});
	board_.getKing(COLORPLAYER1)->moved();
	board_.getKing(COLORPLAYER2)->moved();
}

void Game::start(WhiteToWin2)
{
	//Reshevsky - Fischer Palma de Mallorca Interzonal 1970
	start();
	board_.fill(WhiteToWin2{});
	board_.getKing(COLORPLAYER1)->moved();
	board_.getKing(COLORPLAYER2)->moved();
}


bool Game::canUndo() const
{
	return moveHistory_.size() != 0;
}

bool Game::canRedo() const
{
	return redoHistory_.size() != 0;
}

void Game::undo()
{
	if (moveHistory_.size() > 0)
	{
		auto moveHistory = moveHistory_.back();
		moveHistory_.pop_back();
		auto pieceEat = moveHistory->getPieceEat();
		if(pieceEat)
			piecesEat_.erase(pieceEat);
		board_.restore(moveHistory);
		redoHistory_.push_back(moveHistory);
		changeTurn();
	}

}

void Game::redo()
{
	if (redoHistory_.size() > 0)
	{
		auto moveHistory = redoHistory_.back();
		redoHistory_.pop_back();
		auto piece = board_.getPiece(moveHistory->getFrom());
		auto redos = redoHistory_;
		move(piece,moveHistory->getTo());
		redoHistory_ = redos;
	}

}

void Game::redoClear()
{
	redoHistory_.clear();
}


void Game::changeTurn()
{
	turn_ = board_.getOpponentColor(turn_);
}


std::set<PiecePtr> Game::getPieceEat() const
{
	return piecesEat_;
}


