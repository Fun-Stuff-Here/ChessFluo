/*
* Implémentation de la Classe ChessFluoWindow, Projet-INF1015
*\file		ChessFluoWindow.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967 
*\date		13 avril 2021
* Créé le	13 avril 2021
*/




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

#include <iostream>

#include "ChessBox.h"
#include "Constant.h"
#include "ChessFluoWindow.h"
#include "exeptions.h"

using namespace ChessView;

ChessFluoWindow::ChessFluoWindow(QWidget* parent):
	QMainWindow(parent)
{
	board_ = std::make_shared<ChessModel::Board>();
	selectedPiece_ = ChessModel::Board::pieceNotFound;

	auto mainWidget = new QWidget(this);
	QGridLayout *mainGridLayout = new QGridLayout(mainWidget);
	
	for (int i = 0; i < NROWS; ++i)
	{
		for (size_t j = 0; j < NCOLUMNS; j++)
		{
			ChessModel::Position position{j+1,i+1};
			ChessBoxPtr chessBox = std::make_shared<ChessBox>(board_, position ,this,mainWidget);
			chessBoxes_[position] = chessBox;
			mainGridLayout->addWidget(chessBox.get(),NROWS- i, j);
			mainGridLayout->setSpacing(0);
		}
	}
	//Qobject::connect(&c1, SIGNAL(valueChanged(int)),
	//	&c2, SLOT(setValue(int)));

	
	mainWidget->setLayout(mainGridLayout);
	mainWidget->setMinimumSize(NROWS * CHESSBOXSIZE);
}

void ChessFluoWindow::selections(ChessModel::PiecePtr& piece, ChessBox* chessbox)
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
		auto positions = piece->getMoves();
		positions.push_back(piece->getPosition());
		update(positions, FULLOPACITY);
		selectedPiece_ = ChessModel::Board::pieceNotFound;

	}
	else
	{
		if (selectedPiece_)
		{
			auto previousPositions = selectedPiece_->getMoves();
			previousPositions.push_back(selectedPiece_->getPosition());
			update(previousPositions, FULLOPACITY);
		}

		if (piece)
		{
			auto positions = piece->getMoves();
			positions.push_back(piece->getPosition());
			update(positions, SELECTIONOPACITY);

		}
		selectedPiece_ = piece;
	}

}

void ChessFluoWindow::update()
{
	for (auto&& it : chessBoxes_)
	{
		it.second->update();
	}
}

void ChessFluoWindow::update(std::vector<ChessModel::Position>& positions, const double opacity)
{
	for (auto&& position : positions)
	{
		auto effect = dynamic_cast<QGraphicsOpacityEffect*>(chessBoxes_[position]->graphicsEffect());
		effect->setOpacity(opacity);
	}
}

ChessModel::PiecePtr ChessFluoWindow::move(ChessModel::Position& position)
{
	try
	{
		auto pieceEaten = board_->move(selectedPiece_, position);
		return pieceEaten;
	}
	catch (const ChessModel::ImpossibleMove&)
	{
		QMessageBox::information(nullptr,"Impossible Move", "Ce mouvement est impossible.");
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


bool ChessFluoWindow::isMoving(ChessModel::PiecePtr& piece)
{
	if (piece && selectedPiece_)
		return selectedPiece_->getColor() != piece->getColor();
	else
		return static_cast<bool>(selectedPiece_) && !static_cast<bool>(piece);
}

bool ChessFluoWindow::isSamePiece(ChessModel::PiecePtr& piece)
{
	if (selectedPiece_)
		return selectedPiece_ == piece;
	else
		return false;
}