/*
* Implémentation de la Classe EatView, Projet-INF1015
*\file		EatView.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544, Afaf Djellabi 2089967
*\date		13 avril 2021
* Créé le	13 avril 2021
*/
#include "EatView.h"
#include "exeptions.h"
#include "Game.h"
#include "cppitertools/enumerate.hpp"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <qgridlayout.h>
#include <QGraphicsOpacityEffect>
#include <qmessagebox.h>
#pragma pop()

using namespace ChessView;



EatView::EatView(ChessModel::GamePtr& game, QWidget* parent ):
	QWidget(parent), game_(game)
{
	QGridLayout* middleLayout = new QGridLayout(this);

	QLabel* eatenPiecesLabel = new QLabel(this);
	eatenPiecesLabel->setText("Pièces mangées : ");
	eatenPiecesLabel->setAlignment(Qt::AlignTop);
	eatenPiecesLabel->setAlignment(Qt::AlignLeft);
	middleLayout->addWidget(eatenPiecesLabel,0,0);


	QWidget* piecesIconsGrid = new QWidget(this);
	QGridLayout* piecesIconsGridLayout = new QGridLayout(piecesIconsGrid);
	middleLayout->addWidget(piecesIconsGrid, 1, 0);

	for (size_t i = 0; i < NROWS; i++)
	{
		PieceIconPtr icon = std::make_shared<PieceIcon>(ChessModel::COLORPLAYER1,this);
		eatenPiecesIcons_[ChessModel::COLORPLAYER1].push_back(icon);
		piecesIconsGridLayout->addWidget(icon.get(), i, 0);
		piecesIconsGridLayout->setSpacing(0);
		piecesIconsGridLayout->setVerticalSpacing(0);
	}

	for (size_t i = 0; i < NROWS; i++)
	{
		PieceIconPtr icon = std::make_shared<PieceIcon>(ChessModel::COLORPLAYER2, this);
		eatenPiecesIcons_[ChessModel::COLORPLAYER2].push_back(icon);
		piecesIconsGridLayout->addWidget(icon.get(), i, 1);
		piecesIconsGridLayout->setSpacing(0);
		piecesIconsGridLayout->setVerticalSpacing(0);
	}



	piecesIconsGrid->setLayout(piecesIconsGridLayout);
	piecesIconsGrid->setFixedSize(piecesIconsGridLayout->totalMinimumSize());

	
	setLayout(middleLayout);
	setFixedSize(middleLayout->totalMinimumSize());
	
}

void EatView::update()
{

	
	auto piecesEat = game_->getPieceEat();
	if (nPiece_ > piecesEat.size())
	{
		for (auto&& [color,icons]: eatenPiecesIcons_)
		{
			for (auto&& icon : icons)
				icon->update(ChessModel::Board::pieceNotFound);
		}
	}


	nPiece_ = piecesEat.size();

	std::vector<ChessModel::PiecePtr> whitePieces;
	std::copy_if(piecesEat.begin(), piecesEat.end(), std::back_inserter(whitePieces),
		[](ChessModel::PiecePtr piece) -> bool {
			return piece->getColor()==ChessModel::COLORPLAYER1;
		}
		);


	std::vector<ChessModel::PiecePtr> blackPieces;
	std::copy_if(piecesEat.begin(), piecesEat.end(), std::back_inserter(blackPieces),
		[](ChessModel::PiecePtr piece) -> bool {
			return piece->getColor() == ChessModel::COLORPLAYER2;
		}
	);


	for (auto&& [i, whitePiece] : iter::enumerate(whitePieces))
		eatenPiecesIcons_[whitePiece->getColor()][i]->update(whitePiece);
	
	for (auto&& [i, blackPiece] : iter::enumerate(blackPieces))
		eatenPiecesIcons_[blackPiece->getColor()][i]->update(blackPiece);
}
