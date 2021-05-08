
/*
* Tests sur le model du jeu d'echec, Projet-INF1015
*\file		TestsChessModel.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		12 avril 2021
* Créé le	10 avril 2021
*/
#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <gsl/span>
#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>

#include "Piece.h"
#include "Board.h"
#include "exeptions.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"
#include "Game.h"

#include "Game.h"


using namespace ChessModel;

TEST(Board, too_many_kings)
{
	Game game{};
	game.start();
	auto board = game.getBoard();


	Position  kingPosition1{ 4,4 };
	std::string color = COLORPLAYER1;
	PiecePtr  king(new King{ kingPosition1,color,board });

	board->addPiece(king);

	EXPECT_THROW(game.move(king, { 4,5 }), NotTwoKings);

	Position  kingPosition2{ 5,6 };
	std::string color2 = COLORPLAYER1;
	PiecePtr  king2(new King{ kingPosition2,color2,board });

	Position  kingPosition3{ 3,3 };
	std::string color3 = COLORPLAYER2;
	PiecePtr  king3(new King{ kingPosition3,color3,board });

	EXPECT_THROW(board->addPiece(king2), NotTwoKings);
	board->addPiece(king3);
	EXPECT_THROW(board->addPiece(king), NotTwoKings);

}

TEST(Game, move) {

	Game game;
	game.start(Regular2PlayerGame{});
	Board* board = game.getBoard();

	auto pawn = board->getPiece({ 1,7 });
	auto whitePawn = board->getPiece({ 1,2 });
	Position to{ 1,6 };
	EXPECT_THROW(game.moveTry(pawn, to), ImpossibleMove);
	EXPECT_EQ(game.getMovesPositions(to), std::vector<Position>{});

	game.move(whitePawn, { 1,4 });
	Position expected{ 1,4 };
	auto gotten = whitePawn->getPosition();
	EXPECT_EQ(gotten, expected);

}

TEST(Board, Creation) {

	Board board{};
	// Redirect cout to our stringstream 
	std::stringstream buffer;
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());


	for (auto&& it : board.getPieces())
	{
		std::cout << typeid(*it.second).name() << " " << it.second->getPosition().first << ", " << it.second->getPosition().second << " " << it.second->getColor() << std::endl;
	}

	std::string expected =
		"class ChessModel::Knight 2, 8 vertmoisi\n"
		"class ChessModel::Pawn 8, 2 bluelaite\n"
		"class ChessModel::Bishop 3, 1 bluelaite\n"
		"class ChessModel::Pawn 5, 7 vertmoisi\n"
		"class ChessModel::Knight 7, 8 vertmoisi\n"
		"class ChessModel::Pawn 8, 7 vertmoisi\n"
		"class ChessModel::Bishop 6, 1 bluelaite\n"
		"class ChessModel::Pawn 5, 2 bluelaite\n"
		"class ChessModel::Knight 2, 1 bluelaite\n"
		"class ChessModel::Pawn 1, 2 bluelaite\n"
		"class ChessModel::Pawn 4, 7 vertmoisi\n"
		"class ChessModel::Bishop 3, 8 vertmoisi\n"
		"class ChessModel::Knight 7, 1 bluelaite\n"
		"class ChessModel::Pawn 4, 2 bluelaite\n"
		"class ChessModel::Pawn 1, 7 vertmoisi\n"
		"class ChessModel::Bishop 6, 8 vertmoisi\n"
		"class ChessModel::King 5, 1 bluelaite\n"
		"class ChessModel::Pawn 6, 2 bluelaite\n"
		"class ChessModel::Pawn 3, 7 vertmoisi\n"
		"class ChessModel::King 5, 8 vertmoisi\n"
		"class ChessModel::Rook 1, 1 bluelaite\n"
		"class ChessModel::Rook 8, 8 vertmoisi\n"
		"class ChessModel::Pawn 2, 2 bluelaite\n"
		"class ChessModel::Pawn 7, 7 vertmoisi\n"
		"class ChessModel::Rook 8, 1 bluelaite\n"
		"class ChessModel::Rook 1, 8 vertmoisi\n"
		"class ChessModel::Queen 4, 1 bluelaite\n"
		"class ChessModel::Pawn 7, 2 bluelaite\n"
		"class ChessModel::Pawn 2, 7 vertmoisi\n"
		"class ChessModel::Queen 4, 8 vertmoisi\n"
		"class ChessModel::Pawn 3, 2 bluelaite\n"
		"class ChessModel::Pawn 6, 7 vertmoisi\n";

	std::string text = buffer.str();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(text , expected);

}


TEST(Bishop, test_block_move) {

	Board board{ KingOnly{} };

	std::string color = COLORPLAYER1;
	Position position{ 4,2 };
	PiecePtr bishop(new Bishop{ position,color,&board });
	board.addPiece(bishop);
	PiecePtr king = board.getPiece({ 4,1 });
	board.move(king, { 5,1 });

	std::vector<Position> expected =
	{
		{3,1},
		{3,3},
		{2,4},
		{1,5},
		{5,3},
		{6,4},
		{7,5},
		{8,6}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = bishop->getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);

}



TEST(Knight, moves) {

	Board board;
	Position position = { 5,1 };
	std::string couleur = COLORPLAYER1;
	Knight knigth{ position,couleur,&board };
	std::vector<Position> expected =
	{
		//{3,2},
		{4,3},
		{6,3},
		//{7,2}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = knigth.getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);
}


TEST(Bishop, moves) {

	Board board{ KingOnly{} };
	Position position = { 6,1 };
	std::string couleur = COLORPLAYER1;
	Bishop bishop{ position,couleur,&board };
	std::vector<Position> expected =
	{
		{7, 2},
		{8, 3},
		{5, 2},
		{4, 3},
		{3, 4},
		{2, 5},
		{1, 6}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = bishop.getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);
}

TEST(Rook, moves)
{
	Board board{ KingOnly{} };

	std::string color = COLORPLAYER1;
	Position position{4,3};
	PiecePtr rook(new Rook{ position,color,&board });

	board.addPiece(rook);
	std::vector<Position> expected =
	{
		{4,8},
		{4,7},
		{4,6},
		{4,5},
		{4,4},
		{4,2},
		{1,3},
		{2,3},
		{3,3},
		{5,3},
		{6,3},
		{7,3},
		{8,3}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = rook->getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected, gotten);
}




TEST(Queen, moves)
{
	Board board{ KingOnly{} };

	std::string color = COLORPLAYER1;
	Position position{ 4,3 };
	PiecePtr queen(new Queen{ position,color,&board });

	board.addPiece(queen);
	std::vector<Position> expected =
	{
		{4,8},
		{4,7},
		{4,6},
		{4,5},
		{4,4},
		{4,2},
		{1,3},
		{2,3},
		{3,3},
		{5,3},
		{6,3},
		{7,3},
		{8,3},
		{3,2},
		{2,1},
		{5,4},
		{6,5},
		{7,6},
		{8,7},
		{5,2},
		{6,1},
		{3,4},
		{2,5},
		{1,6}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = queen->getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected, gotten);
}



TEST(Bishop , block_move) {

	Board board{};
	Position position = { 6,1 };
	std::string couleur = COLORPLAYER1;
	Bishop bishop{ position,couleur,&board };
	std::vector<Position> expected =
	{};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = bishop.getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);
}



TEST(Bishop, eat) {
	Board board;
	PiecePtr bishop = board.getPiece({ 3,8 });

	PiecePtr pawn = board.getPiece({ 4,7 });
	board.move(pawn, { 4,5 });
	board.move(bishop, { 6,5 });

	std::vector<Position> expected ={ Position(4, 7), Position(5, 6) };
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = bishop->getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);

}



TEST(Bishop, eaten) {
	Board board;
	PiecePtr bishopRight2 = board.getPiece({ 6,8 });
	PiecePtr pawn1 = board.getPiece({5,7});
	board.move(pawn1, { 5,5 });
	board.move(bishopRight2, { 1,3 });

	PiecePtr pawn = board.getPiece({ 2,2 });
	PiecePtr eatenPiece = board.move(bishopRight2, { 2,2});
	EXPECT_EQ(pawn.get() , eatenPiece.get());
}



TEST(Board, inserting_Piece)
{
	Board board{ KingOnly{} };

	std::string color = COLORPLAYER1;
	Position p1{ 3, 1 };
	PiecePtr piece1(new Bishop{ p1,color,&board });


	board.addPiece(piece1);

	// Redirect cout to our stringstream 
	std::stringstream buffer;
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());
	board.addPiece(piece1);


	for (auto&& it : board.getPieces())
	{
		std::cout << typeid(*it.second).name() << " " << it.second->getPosition().first << ", " << it.second->getPosition().second << " " << it.second->getColor() << std::endl;
	}

	std::string expected =
		"Already a piece at position 3, 1\n"
		"class ChessModel::King 4, 1 bluelaite\n"
		"class ChessModel::King 4, 8 vertmoisi\n"
		"class ChessModel::Bishop 3, 1 bluelaite\n";

	// When done redirect cout to its old self
	std::string text = buffer.str();
	std::cout.rdbuf(sbuf);
	EXPECT_EQ(text , expected);
}








TEST(Game, getter)
{
	Game game{};

	//test getBoard()
	EXPECT_TRUE(game.getBoard() != nullptr);

	//test1 getTurn()
	std::string expectedTurn1 = COLORPLAYER1;
	EXPECT_TRUE(game.getTurn() == expectedTurn1);

	//test2 getTurn()
	game.changeTurn();
	std::string expectedTurn2 = COLORPLAYER2;
	EXPECT_TRUE(game.getTurn() == expectedTurn2);

	//test1 isValidMove(from, to)
	std::string color = COLORPLAYER1;
	Position  kingPosition1{ 4,1 };
	PiecePtr  king1(new King{ kingPosition1,color,game.getBoard() });

	Position  rookPosition1{ 1,7 };
	PiecePtr  rook1(new Rook{ rookPosition1,color,game.getBoard() });

	color = COLORPLAYER2;
	Position  kingPosition2{ 7,8 };
	PiecePtr  king2(new King{ kingPosition2,color,game.getBoard() });

	Position  pawnPosition1{ 6,7 };
	PiecePtr  pawn1(new Pawn{ pawnPosition1,color,game.getBoard() });

	Position  pawnPosition2{ 7,7 };
	PiecePtr  pawn2(new Pawn{ pawnPosition2,color,game.getBoard() });

	Position  pawnPosition3{ 8,7 };
	PiecePtr  pawn3(new Pawn{ pawnPosition3,color,game.getBoard() });

	game.getBoard()->addPiece(king1);
	game.getBoard()->addPiece(rook1);
	game.getBoard()->addPiece(king2);
	game.getBoard()->addPiece(pawn1);
	game.getBoard()->addPiece(pawn2);
	game.getBoard()->addPiece(pawn3);

	Position to{ 1, 8 };
	game.changeTurn();
	EXPECT_TRUE(game.isValidMove(rookPosition1, to));

	//test1 isEnded()
	EXPECT_FALSE(game.isEnded());

	//test2 isCheckMate(color) and isEnded()
	game.getBoard()->move(rook1, to);
	EXPECT_TRUE(game.isCheckMate(COLORPLAYER2));
	EXPECT_TRUE(game.isEnded());
}

TEST(Game, getPieceEat) {
	Game game{};
	std::string color = COLORPLAYER1;
	Position  kingPosition1{ 4,1 };
	PiecePtr  king1(new King{ kingPosition1,color,game.getBoard() });

	Position knightPosition1{ 4, 4 };
	PiecePtr knight1(new Knight{ knightPosition1, color, game.getBoard() });

	Position pawnPosition1{ 1, 4 };
	PiecePtr pawn1(new Pawn{ pawnPosition1, color, game.getBoard() });

	color = COLORPLAYER2;
	Position kingPosition2{ 4, 8 };
	PiecePtr king2(new King{ kingPosition2, color, game.getBoard() });

	Position bishopPosition2{ 2, 5 };
	PiecePtr bishop2(new Bishop{ bishopPosition2, color, game.getBoard() });

	Position pawnPosition2{ 1, 6 };
	PiecePtr pawn2(new Pawn{ pawnPosition2, color, game.getBoard() });

	game.getBoard()->addPiece(king1);
	game.getBoard()->addPiece(knight1);
	game.getBoard()->addPiece(pawn1);
	game.getBoard()->addPiece(king2);
	game.getBoard()->addPiece(bishop2);
	game.getBoard()->addPiece(pawn2);

	std::set<PiecePtr> eatenPiecesExpected = {};
	EXPECT_TRUE(game.getPieceEat() == eatenPiecesExpected);

	game.move(knight1, bishopPosition2);
	game.move(pawn2, bishopPosition2);
	game.move(pawn1, bishopPosition2);
	eatenPiecesExpected.insert(bishop2);
	eatenPiecesExpected.insert(knight1);
	eatenPiecesExpected.insert(pawn2);
	EXPECT_TRUE(game.getPieceEat() == eatenPiecesExpected);
	EXPECT_EQ(game.getPieceEat().size(), 3);

}

TEST(Game, regular2PlayerStart)
{
	Game game{};
	game.start(Regular2PlayerGame{});

	// Redirect cout to our stringstream 
	std::stringstream buffer;
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	for (auto&& it : game.getBoard()->getPieces())
	{
		std::cout << typeid(*it.second).name() << " " << it.second->getPosition().first << ", " << it.second->getPosition().second << " " << it.second->getColor() << std::endl;
	}

	std::string expected =
		"class ChessModel::Knight 2, 8 vertmoisi\n"
		"class ChessModel::Pawn 8, 2 bluelaite\n"
		"class ChessModel::Bishop 3, 1 bluelaite\n"
		"class ChessModel::Pawn 5, 7 vertmoisi\n"
		"class ChessModel::Knight 7, 8 vertmoisi\n"
		"class ChessModel::Pawn 8, 7 vertmoisi\n"
		"class ChessModel::Bishop 6, 1 bluelaite\n"
		"class ChessModel::Pawn 5, 2 bluelaite\n"
		"class ChessModel::Knight 2, 1 bluelaite\n"
		"class ChessModel::Pawn 1, 2 bluelaite\n"
		"class ChessModel::Pawn 4, 7 vertmoisi\n"
		"class ChessModel::Bishop 3, 8 vertmoisi\n"
		"class ChessModel::Knight 7, 1 bluelaite\n"
		"class ChessModel::Pawn 4, 2 bluelaite\n"
		"class ChessModel::Pawn 1, 7 vertmoisi\n"
		"class ChessModel::Bishop 6, 8 vertmoisi\n"
		"class ChessModel::King 5, 1 bluelaite\n"
		"class ChessModel::Pawn 6, 2 bluelaite\n"
		"class ChessModel::Pawn 3, 7 vertmoisi\n"
		"class ChessModel::King 5, 8 vertmoisi\n"
		"class ChessModel::Rook 1, 1 bluelaite\n"
		"class ChessModel::Rook 8, 8 vertmoisi\n"
		"class ChessModel::Pawn 2, 2 bluelaite\n"
		"class ChessModel::Pawn 7, 7 vertmoisi\n"
		"class ChessModel::Rook 8, 1 bluelaite\n"
		"class ChessModel::Rook 1, 8 vertmoisi\n"
		"class ChessModel::Queen 4, 1 bluelaite\n"
		"class ChessModel::Pawn 7, 2 bluelaite\n"
		"class ChessModel::Pawn 2, 7 vertmoisi\n"
		"class ChessModel::Queen 4, 8 vertmoisi\n"
		"class ChessModel::Pawn 3, 2 bluelaite\n"
		"class ChessModel::Pawn 6, 7 vertmoisi\n";

	std::string text = buffer.str();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(text, expected);
}

TEST(Game, regular1PlayerStart)
{
	Game game{};
	game.start(Regular1PlayerGame{});

	// Redirect cout to our stringstream 
	std::stringstream buffer;
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	for (auto&& it : game.getBoard()->getPieces())
	{
		std::cout << typeid(*it.second).name() << " " << it.second->getPosition().first << ", " << it.second->getPosition().second << " " << it.second->getColor() << std::endl;
	}

	std::string expected =
		"class ChessModel::Knight 2, 8 vertmoisi\n"
		"class ChessModel::Pawn 8, 2 bluelaite\n"
		"class ChessModel::Bishop 3, 1 bluelaite\n"
		"class ChessModel::Pawn 5, 7 vertmoisi\n"
		"class ChessModel::Knight 7, 8 vertmoisi\n"
		"class ChessModel::Pawn 8, 7 vertmoisi\n"
		"class ChessModel::Bishop 6, 1 bluelaite\n"
		"class ChessModel::Pawn 5, 2 bluelaite\n"
		"class ChessModel::Knight 2, 1 bluelaite\n"
		"class ChessModel::Pawn 1, 2 bluelaite\n"
		"class ChessModel::Pawn 4, 7 vertmoisi\n"
		"class ChessModel::Bishop 3, 8 vertmoisi\n"
		"class ChessModel::Knight 7, 1 bluelaite\n"
		"class ChessModel::Pawn 4, 2 bluelaite\n"
		"class ChessModel::Pawn 1, 7 vertmoisi\n"
		"class ChessModel::Bishop 6, 8 vertmoisi\n"
		"class ChessModel::King 5, 1 bluelaite\n"
		"class ChessModel::Pawn 6, 2 bluelaite\n"
		"class ChessModel::Pawn 3, 7 vertmoisi\n"
		"class ChessModel::King 5, 8 vertmoisi\n"
		"class ChessModel::Rook 1, 1 bluelaite\n"
		"class ChessModel::Rook 8, 8 vertmoisi\n"
		"class ChessModel::Pawn 2, 2 bluelaite\n"
		"class ChessModel::Pawn 7, 7 vertmoisi\n"
		"class ChessModel::Rook 8, 1 bluelaite\n"
		"class ChessModel::Rook 1, 8 vertmoisi\n"
		"class ChessModel::Queen 4, 1 bluelaite\n"
		"class ChessModel::Pawn 7, 2 bluelaite\n"
		"class ChessModel::Pawn 2, 7 vertmoisi\n"
		"class ChessModel::Queen 4, 8 vertmoisi\n"
		"class ChessModel::Pawn 3, 2 bluelaite\n"
		"class ChessModel::Pawn 6, 7 vertmoisi\n";

	std::string text = buffer.str();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(text, expected);
}

TEST(Game, whiteToCheckMate1Start)
{
	Game game{};
	game.start(WhiteToCheckMate1{});

	// Redirect cout to our stringstream 
	std::stringstream buffer;
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	for (auto&& it : game.getBoard()->getPieces())
	{
		std::cout << typeid(*it.second).name() << " " << it.second->getPosition().first << ", " << it.second->getPosition().second << " " << it.second->getColor() << std::endl;
	}

	std::string expected =
		"class ChessModel::Rook 1, 8 vertmoisi\n"
		"class ChessModel::Pawn 3, 4 vertmoisi\n"
		"class ChessModel::Pawn 2, 5 vertmoisi\n"
		"class ChessModel::Queen 1, 6 vertmoisi\n"
		"class ChessModel::Rook 6, 1 bluelaite\n"
		"class ChessModel::Knight 3, 5 vertmoisi\n"
		"class ChessModel::King 7, 1 bluelaite\n"
		"class ChessModel::Bishop 4, 7 vertmoisi\n"
		"class ChessModel::Bishop 5, 7 vertmoisi\n"
		"class ChessModel::Knight 7, 5 vertmoisi\n"
		"class ChessModel::Bishop 3, 1 bluelaite\n"
		"class ChessModel::Pawn 5, 5 vertmoisi\n"
		"class ChessModel::Pawn 6, 6 vertmoisi\n"
		"class ChessModel::King 7, 7 vertmoisi\n"
		"class ChessModel::Pawn 2, 2 bluelaite\n"
		"class ChessModel::Pawn 3, 3 bluelaite\n"
		"class ChessModel::Pawn 8, 5 vertmoisi\n"
		"class ChessModel::Pawn 8, 7 vertmoisi\n"
		"class ChessModel::Bishop 3, 2 bluelaite\n"
		"class ChessModel::Pawn 4, 5 bluelaite\n"
		"class ChessModel::Pawn 7, 2 bluelaite\n"
		"class ChessModel::Queen 8, 4 bluelaite\n"
		"class ChessModel::Knight 8, 6 bluelaite\n";

	std::string text = buffer.str();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(text, expected);
}

TEST(Game, whiteToCheckMate2Start)
{
	Game game{};
	game.start(WhiteToCheckMate2{});

	// Redirect cout to our stringstream 
	std::stringstream buffer;
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	for (auto&& it : game.getBoard()->getPieces())
	{
		std::cout << typeid(*it.second).name() << " " << it.second->getPosition().first << ", " << it.second->getPosition().second << " " << it.second->getColor() << std::endl;
	}

	std::string expected =
		"class ChessModel::Rook 1, 8 vertmoisi\n"
		"class ChessModel::Pawn 1, 7 vertmoisi\n"
		"class ChessModel::King 7, 1 bluelaite\n"
		"class ChessModel::Bishop 3, 6 vertmoisi\n"
		"class ChessModel::Pawn 2, 7 vertmoisi\n"
		"class ChessModel::Knight 4, 8 vertmoisi\n"
		"class ChessModel::Pawn 3, 4 vertmoisi\n"
		"class ChessModel::Pawn 4, 6 vertmoisi\n"
		"class ChessModel::Rook 5, 7 bluelaite\n"
		"class ChessModel::Knight 7, 5 bluelaite\n"
		"class ChessModel::King 8, 8 vertmoisi\n"
		"class ChessModel::Pawn 7, 7 vertmoisi\n"
		"class ChessModel::Pawn 3, 3 bluelaite\n"
		"class ChessModel::Pawn 4, 4 bluelaite\n"
		"class ChessModel::Pawn 8, 7 vertmoisi\n"
		"class ChessModel::Pawn 1, 2 bluelaite\n"
		"class ChessModel::Pawn 6, 5 bluelaite\n"
		"class ChessModel::Bishop 4, 5 bluelaite\n"
		"class ChessModel::Pawn 8, 2 bluelaite\n";

	std::string text = buffer.str();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(text, expected);
}


TEST(Game, whiteToWin1Start)
{
	Game game{};
	game.start(WhiteToWin1{});

	// Redirect cout to our stringstream 
	std::stringstream buffer;
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	for (auto&& it : game.getBoard()->getPieces())
	{
		std::cout << typeid(*it.second).name() << " " << it.second->getPosition().first << ", " << it.second->getPosition().second << " " << it.second->getColor() << std::endl;
	}

	std::string expected =
		"class ChessModel::Bishop 2, 7 vertmoisi\n"
		"class ChessModel::Pawn 7, 2 bluelaite\n"
		"class ChessModel::Rook 5, 8 vertmoisi\n"
		"class ChessModel::Pawn 7, 6 vertmoisi\n"
		"class ChessModel::Queen 6, 7 vertmoisi\n"
		"class ChessModel::Rook 3, 2 vertmoisi\n"
		"class ChessModel::Pawn 5, 3 vertmoisi\n"
		"class ChessModel::Pawn 1, 7 vertmoisi\n"
		"class ChessModel::King 7, 1 bluelaite\n"
		"class ChessModel::Pawn 2, 6 vertmoisi\n"
		"class ChessModel::King 7, 8 vertmoisi\n"
		"class ChessModel::Pawn 8, 7 vertmoisi\n"
		"class ChessModel::Pawn 1, 2 bluelaite\n"
		"class ChessModel::Bishop 7, 7 bluelaite\n"
		"class ChessModel::Pawn 2, 2 bluelaite\n"
		"class ChessModel::Pawn 4, 4 bluelaite\n"
		"class ChessModel::Rook 1, 1 bluelaite\n"
		"class ChessModel::Pawn 6, 6 bluelaite\n"
		"class ChessModel::Rook 6, 4 bluelaite\n"
		"class ChessModel::Queen 8, 4 bluelaite\n"
		"class ChessModel::Pawn 8, 2 bluelaite\n";

	std::string text = buffer.str();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(text, expected);
}

TEST(Game, whiteToWin2Start)
{
	Game game{};
	game.start(WhiteToWin2{});

	// Redirect cout to our stringstream 
	std::stringstream buffer;
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

	for (auto&& it : game.getBoard()->getPieces())
	{
		std::cout << typeid(*it.second).name() << " " << it.second->getPosition().first << ", " << it.second->getPosition().second << " " << it.second->getColor() << std::endl;
	}

	std::string expected =
		"class ChessModel::Rook 3, 8 vertmoisi\n"
		"class ChessModel::Pawn 8, 7 vertmoisi\n"
		"class ChessModel::Queen 5, 2 vertmoisi\n"
		"class ChessModel::Bishop 8, 6 vertmoisi\n"
		"class ChessModel::Pawn 1, 7 vertmoisi\n"
		"class ChessModel::Pawn 5, 3 bluelaite\n"
		"class ChessModel::Pawn 2, 7 vertmoisi\n"
		"class ChessModel::Rook 4, 1 bluelaite\n"
		"class ChessModel::King 1, 8 vertmoisi\n"
		"class ChessModel::Pawn 5, 4 vertmoisi\n"
		"class ChessModel::Pawn 3, 2 bluelaite\n"
		"class ChessModel::Pawn 1, 2 bluelaite\n"
		"class ChessModel::King 2, 1 bluelaite\n"
		"class ChessModel::Bishop 3, 1 bluelaite\n"
		"class ChessModel::Pawn 2, 2 bluelaite\n"
		"class ChessModel::Queen 5, 5 bluelaite\n";

	std::string text = buffer.str();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(text, expected);
}

TEST(Game, undo_redo) 
{
	Game game{};
	game.start(Regular2PlayerGame{});

	//test canUndo() and canRedo()
	EXPECT_FALSE(game.canUndo());
	EXPECT_FALSE(game.canRedo());

	auto blackPawn = game.getBoard()->getPiece({ 5,2 });
	game.move(blackPawn, { 5,3 });

	EXPECT_TRUE(game.canUndo());
	EXPECT_FALSE(game.canRedo());

	game.undo();
	EXPECT_FALSE(game.canUndo());
	EXPECT_TRUE(game.canRedo());

	game.redo();
	EXPECT_TRUE(game.canUndo());
	EXPECT_FALSE(game.canRedo());

	
	Game game2{};
	game2.start();
	std::string color = COLORPLAYER1;
	Position  kingPosition1{ 5,1 };
	PiecePtr  king1(new King{ kingPosition1,color,game2.getBoard() });

	Position knightPosition1{ 4, 4 };
	PiecePtr knight1(new Knight{ knightPosition1, color, game2.getBoard() });

	color = COLORPLAYER2;
	Position kingPosition2{ 5, 8 };
	PiecePtr king2(new King{ kingPosition2, color, game2.getBoard() });

	Position bishopPosition2{ 2, 5 };
	PiecePtr bishop2(new Bishop{ bishopPosition2, color, game2.getBoard() });

	game2.getBoard()->addPiece(king1);
	game2.getBoard()->addPiece(knight1);
	game2.getBoard()->addPiece(king2);
	game2.getBoard()->addPiece(bishop2);

	game2.move(knight1, bishopPosition2);
	EXPECT_TRUE(game2.canUndo());
	EXPECT_FALSE(game2.canRedo());
	
	game2.undo();
	EXPECT_FALSE(game2.canUndo());
	EXPECT_TRUE(game2.canRedo());

	game2.redo();
	EXPECT_TRUE(game2.canUndo());
	EXPECT_FALSE(game2.canRedo());
}

TEST(Game, checkMate) {
	Game game{};
	game.start(Regular2PlayerGame{});
	EXPECT_NO_THROW(game.isCheckMate(COLORPLAYER1));


	auto blackPawn = game.getBoard()->getPiece({5,2});
	auto blackQuenn = game.getBoard()->getPiece({ 4,1 });
	auto blackBishop = game.getBoard()->getPiece({ 6,1 });
	auto whitePawn = game.getBoard()->getPiece({ 1,7 });

	game.move(blackPawn, {5,3});
	game.move(whitePawn, { 1,6 });
	game.move(blackQuenn, { 6,3 });
	game.move(whitePawn, { 1,5 });
	game.move(blackBishop, { 3,4 });
	game.move(whitePawn, { 1,4 });
	EXPECT_THROW(game.move(blackQuenn, { 6,7 }), CheckMate);

}


TEST(Game, check)
{
	Game game{};
	game.start(Regular2PlayerGame{});
	auto board = game.getBoard();

	auto WhitePawn = board->getPiece({5,2});
	auto whiteBishop = board->getPiece({ 6,1 });
	
	auto blackPawn = board->getPiece({ 4,7 });

	game.move(WhitePawn, { 5,4 });
	game.move(blackPawn, {4,5});
	EXPECT_THROW(game.move(whiteBishop, {2,5}), Check);

}


TEST(Game, getAllPossibleMoves) {
	Game game{};
	game.start(Regular2PlayerGame{});
	auto moves = game.getMovesPositions({1,1});
	EXPECT_EQ(moves.size() , 0);


}
TEST(Game, setter) {

	Game game;
	game.changeTurn();
	std::string gotten = game.getTurn();
	std::string expected = "vertmoisi";

	EXPECT_EQ(gotten, expected);

}




TEST(Game, rook_moves)
{
	Game game{};
	game.start( Regular2PlayerGame{} );
	auto board = game.getBoard();

	auto blackLeftRook = board->getPiece({1,8});
	auto blackLeftPawn = board->getPiece({1,7});

	auto blackRightRook = board->getPiece({ 8,8 });
	auto blackRightPawn = board->getPiece({8,7});

	auto whiteLeftRook = board->getPiece({1,1});
	auto whiteLeftPawn = board->getPiece({1,2});

	auto whiteRightRook = board->getPiece({8,1});
	auto whiteRightPawn = board->getPiece({8,2});

	auto whiteKing = board->getKing(COLORPLAYER1);
	auto blackKing = board->getKing(COLORPLAYER2);

	game.move(whiteLeftPawn, {1,4});
	game.move(blackLeftPawn, { 1,5 });
	game.move(whiteRightPawn, {8,4});
	game.move(blackRightPawn, { 8,5 });

	EXPECT_TRUE(whiteKing->canSmallCastle());
	EXPECT_TRUE(whiteKing->canBigCastle());
	EXPECT_TRUE(blackKing->canSmallCastle());
	EXPECT_TRUE(blackKing->canBigCastle());

	game.move(whiteLeftRook, { 1,2 });
	EXPECT_FALSE(whiteKing->canBigCastle());
	EXPECT_TRUE(whiteKing->canSmallCastle());

	game.move(blackLeftRook, { 1,6 });
	EXPECT_FALSE(blackKing->canBigCastle());
	EXPECT_TRUE(blackKing->canSmallCastle());

	game.move(whiteRightRook, { 8,2 });
	EXPECT_FALSE(whiteKing->canSmallCastle());
	EXPECT_FALSE(whiteKing->canBigCastle());

	game.move(blackRightRook, { 8,6 });
	EXPECT_FALSE(blackKing->canSmallCastle());
	EXPECT_FALSE(blackKing->canBigCastle());

	game.move(whiteLeftRook, { 1,1 });
	game.move(blackLeftRook, { 2,6 });
	game.move(whiteLeftRook, { 1,2 });
	game.move(blackLeftRook, { 2,4 });
	game.move(whiteLeftRook, { 1,1 });
	game.move(blackLeftRook, { 1,4 });
	
}


TEST(PromotionMove, promotion) {

	Game game{};
	game.start(Regular2PlayerGame{});

	auto board = game.getBoard();

	auto whitePawn = board->getPiece({8,2});

	auto blackPawn = board->getPiece({ 1,7 });

	game.move(whitePawn, { 8,4 });
	game.move(blackPawn, { 1,5 });
	game.move(whitePawn, {8,5});
	game.move(blackPawn, { 1,4 });
	game.move(whitePawn, { 8,6 });
	game.move(blackPawn, { 1,3 });
	game.move(whitePawn, { 7,7 });
	game.move(blackPawn, { 2,2 });
	game.move(whitePawn, { 8,8 });
	game.move(blackPawn, {1,1});

	auto whiteQueen = board->getPiece({ 8,8 });
	auto whiteColor = whiteQueen->getColor();
	EXPECT_TRUE(dynamic_cast<Queen*>(whiteQueen.get()));
	EXPECT_EQ(whiteColor, COLORPLAYER1);

	auto blackQueen = board->getPiece({ 1,1 });
	auto blackColor = blackQueen->getColor();
	EXPECT_TRUE(dynamic_cast<Queen*>(blackQueen.get()));
	EXPECT_EQ(blackColor, COLORPLAYER2);

}


TEST(Board, Black_Small_Castle) {
	Game game{};
	game.start(Regular2PlayerGame{});
	Board* board = game.getBoard();

	auto blackKing = board->getPiece({5,1});
	auto blackBishop = board->getPiece({ 6,1 });
	auto blackKnight = board->getPiece({ 7,1 });
	auto blackPawn = board->getPiece({ 7,2 });

	auto whiteKnight = board->getPiece({ 2,8 });

	game.move(blackPawn, { 7,3 });
	game.move(whiteKnight, { 1,6 });
	game.move(blackKnight, { 8,3 });
	game.move(whiteKnight, { 2,8 });
	game.move(blackBishop, { 7,2 });
	game.move(whiteKnight, { 1,6 });
	game.move(blackKing, { 7,1 });


	auto rook = board->getPiece({ 6,1 });
	EXPECT_TRUE(dynamic_cast<Rook*>(rook.get()));
	Position kingPosition{7,1};
	EXPECT_EQ(kingPosition, blackKing->getPosition());
}


TEST(Board, Black_Big_Castle) {
	Game game{};
	game.start(Regular2PlayerGame{});
	Board* board = game.getBoard();

	auto blackKing = board->getPiece({ 5,1 });
	auto blackBishop = board->getPiece({ 3,1 });
	auto blackKnight = board->getPiece({ 2,1 });
	auto blackPawn = board->getPiece({ 4,2 });
	auto blackQueen = board->getPiece({ 4,1 });

	auto whiteKnight = board->getPiece({ 2,8 });

	game.move(blackPawn, { 4,3 });
	game.move(whiteKnight, { 1,6 });
	game.move(blackKnight, { 1,3 });
	game.move(whiteKnight, { 2,8 });
	game.move(blackBishop, { 8,6 });
	game.move(whiteKnight, { 1,6 });
	game.move(blackQueen, { 4,2 });
	game.move(whiteKnight, { 2,8 });
	game.move(blackKing, { 3,1 });

	auto rook = board->getPiece({ 4,1 });
	EXPECT_TRUE(dynamic_cast<Rook*>(rook.get()));
	Position kingPosition{ 3,1 };
	EXPECT_EQ(kingPosition, blackKing->getPosition());
}

TEST(Board, White_Big_Castle) {
	Game game{};
	game.start(Regular2PlayerGame{});
	Board* board = game.getBoard();

	auto blackKing = board->getPiece({ 5,8 });
	auto blackBishop = board->getPiece({ 3,8 });
	auto blackKnight = board->getPiece({ 2,8 });
	auto blackPawn = board->getPiece({ 4,7 });
	auto blackQueen = board->getPiece({ 4,8 });

	auto whiteKnight = board->getPiece({ 2,1 });
	auto whitePawn = board->getPiece({ 1,2 });

	game.move(whitePawn, { 1,4 });
	game.move(blackPawn, { 4,5 });
	game.move(whiteKnight, { 1,3 });
	game.move(blackKnight, { 1,6 });
	game.move(whiteKnight, { 2,1 });
	game.move(blackBishop, { 8,3 });
	game.move(whiteKnight, { 1,3 });
	game.move(blackQueen, { 4,7 });
	game.move(whiteKnight, { 2,1 });
	game.move(blackKing, { 3,8 });

	auto rook = board->getPiece({ 4,8 });
	EXPECT_TRUE(dynamic_cast<Rook*>(rook.get()));
	Position kingPosition{ 3,8 };
	EXPECT_EQ(kingPosition, blackKing->getPosition());
}

TEST(Board, White_Small_Castle) {
	Game game{};
	game.start(Regular2PlayerGame{});
	Board* board = game.getBoard();

	auto blackKing = board->getPiece({ 5,8 });
	auto blackBishop = board->getPiece({ 6,8 });
	auto blackKnight = board->getPiece({ 7,8 });
	auto blackPawn = board->getPiece({ 7,7 });

	auto whiteKnight = board->getPiece({ 2,1 });
	auto whitePawn = board->getPiece({ 1,2 });

	game.move(whitePawn, { 1,4 });
	game.move(blackPawn, { 7,5 });
	game.move(whiteKnight, { 1,3 });
	game.move(blackKnight, { 8,6 });
	game.move(whiteKnight, { 2,1 });
	game.move(blackBishop, { 7,7 });
	game.move(whiteKnight, { 1,3 });
	game.move(blackKing, { 7,8 });


	auto rook = board->getPiece({ 6,8 });
	EXPECT_TRUE(dynamic_cast<Rook*>(rook.get()));
	Position kingPosition{ 7,8 };
	EXPECT_EQ(kingPosition, blackKing->getPosition());
}




#endif
