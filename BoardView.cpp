/*
* Implémentation de la Classe BoardView, Projet-INF1015
*\file		BoardView.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#include "BoardView.h"
#include "exeptions.h"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <qgridlayout.h>
#include <QGraphicsOpacityEffect>
#include <qmessagebox.h>
#pragma pop()


using namespace ChessView;


BoardView::BoardView(QWidget* parent):
	QWidget(parent)
{
	game_  = std::make_shared<ChessModel::Game>();
	selectedPiece_ = ChessModel::Board::pieceNotFound;

	QGridLayout* boardLayout = new QGridLayout(this);

	for (int i = 0; i < NROWS; ++i)
	{
		for (size_t j = 0; j < NCOLUMNS; j++)
		{
			ChessModel::Position position{ j + 1,i + 1 };
			ChessBoxPtr chessBox = std::make_shared<ChessBox>(game_, position, this);
			chessBoxes_[position] = chessBox;
			boardLayout->addWidget(chessBox.get(), NROWS - i, j);
			boardLayout->setSpacing(0);
		}
	}

}



void BoardView::selections(ChessModel::PiecePtr& piece, ChessBox* chessbox)
{

	if (isMoving(piece))
	{
		ChessModel::Position positionTo = chessbox->getPosition();
		move(positionTo);
		update();
		selectedPiece_ = ChessModel::Board::pieceNotFound;
	}
	else if (isSamePiece(piece))
	{
		auto positions = game_->getMovesPositions(piece->getPosition());
		positions.push_back(piece->getPosition());
		update(positions, FULLOPACITY);
		selectedPiece_ = ChessModel::Board::pieceNotFound;

	}
	else
	{
		if (selectedPiece_)
		{
			auto previousPositions = game_->getMovesPositions(selectedPiece_->getPosition());
			previousPositions.push_back(selectedPiece_->getPosition());
			update(previousPositions, FULLOPACITY);
		}

		if (piece)
		{
			auto positions = game_->getMovesPositions(piece->getPosition());
			positions.push_back(piece->getPosition());
			update(positions, SELECTIONOPACITY);

		}
		selectedPiece_ = piece;
	}

}

void BoardView::update()
{
	for (auto&& it : chessBoxes_)
	{
		it.second->update();
	}
}

void BoardView::update(std::vector<ChessModel::Position>& positions, const double opacity)
{
	for (auto&& position : positions)
	{
		auto effect = dynamic_cast<QGraphicsOpacityEffect*>(chessBoxes_[position]->graphicsEffect());
		effect->setOpacity(opacity);
	}
}

ChessModel::PiecePtr BoardView::move(ChessModel::Position& position)
{
	try
	{
		auto pieceEaten = game_->move(selectedPiece_, position);
		return pieceEaten;
	}
	catch (const ChessModel::ImpossibleMove&)
	{
		QMessageBox::information(nullptr, "Impossible Move", "Ce mouvement est impossible.");
	}
	catch (const ChessModel::Check&)
	{
		QMessageBox::information(nullptr, "Check", "Check");
	}
	catch (const ChessModel::Promotion&)
	{
		QMessageBox::information(nullptr, "Promotion", "Pawn reached end");
	}

	return ChessModel::Board::pieceNotFound;
}


bool BoardView::isMoving(ChessModel::PiecePtr& piece)
{
	if (piece && selectedPiece_)
		return selectedPiece_->getColor() != piece->getColor();
	else
		return static_cast<bool>(selectedPiece_) && !static_cast<bool>(piece);
}

bool BoardView::isSamePiece(ChessModel::PiecePtr& piece)
{
	if (selectedPiece_)
		return selectedPiece_ == piece;
	else
		return false;
}