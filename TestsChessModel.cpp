
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


using namespace ChessModel;


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

TEST(Knight, test_block_move) {


	Board board;
	std::string couleur = COLORPLAYER1;
	PiecePtr bishop = board.getPiece({ 3,1 });
	EXPECT_THROW(board.move(bishop, { 5,2 }), ImpossibleMove);
	PiecePtr pawn = board.getPiece({ 4,2 });
	board.move(pawn, {4,4});
	board.move(bishop, { 4,2 });
	PiecePtr knight = board.getPiece({ 2,1 });
	std::vector<Position> expected =
	{
		{1,3},
		//{4,2}, blocked by bishop
		{3,3}
	};

	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = knight->getMoves();
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

TEST(Piece, move_out_of_bound) {

	Board board;
	auto piece = board.getPiece({3,1});
	EXPECT_THROW(board.move(piece, {14,19}),ImpossibleMove);
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
	EXPECT_THROW(board.move(bishop, { 5,2 }), ImpossibleMove);

	PiecePtr pawn = board.getPiece({ 4,7 });
	board.move(pawn, { 4,5 });
	board.move(bishop, { 6,5 });

	std::vector<Position> expected =
	{
		{3, 2},
		{4, 3},
		{5, 4},
		{7, 6},
		{7, 4},
		{8, 3},
		{5, 6},
		{4, 7},
		{3, 8}
	};
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

TEST(Board, piece_remove) {
	Board board;
	PiecePtr bishopRight2 = board.getPiece({ 6,8 });
	PiecePtr pawn1 = board.getPiece({5,7});
	board.move(pawn1, { 5,5 });
	board.move(bishopRight2, { 1,3 });


	PiecePtr pawn = board.getPiece({ 2,2 });
	PiecePtr eatenPiece = board.move(pawn, { 1,3 });
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
		"class ChessModel::Pawn 1, 3 bluelaite\n"
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
		"class ChessModel::King 5, 1 bluelaite\n"
		"class ChessModel::Pawn 6, 2 bluelaite\n"
		"class ChessModel::Pawn 3, 7 vertmoisi\n"
		"class ChessModel::King 5, 8 vertmoisi\n"
		"class ChessModel::Rook 1, 1 bluelaite\n"
		"class ChessModel::Rook 8, 8 vertmoisi\n"
		"class ChessModel::Pawn 7, 7 vertmoisi\n"
		"class ChessModel::Pawn 5, 5 vertmoisi\n"
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

//
//TEST(Board , checking)
//{
//	Board board{ Empty{} };
//
//
//	std::string color1 = COLORPLAYER1;
//	Position p1{ 4, 4 };
//	PiecePtr piece1(new Bishop{ p1,color1,&board });
//	board.addPiece(piece1);
//
//	std::string color2 = COLORPLAYER2;
//	Position p2{ 6, 6 };
//	PiecePtr piece2(new King{ p2,color2,&board });
//	board.addPiece(piece2);
//
//	std::string colorking = COLORPLAYER1;
//	Position pking{ 1, 1 };
//	PiecePtr king(new King{ pking,colorking,&board });
//	board.addPiece(king);
//
//	EXPECT_THROW(board.verifieCheck(color2), Check);
//
//
//	std::string color3 = COLORPLAYER2;
//	Position p3{ 5, 5 };
//	PiecePtr piece3(new Knight{ p3,color3,&board });
//	board.addPiece(piece3);
//	board.verifieCheck(color2);
//
//
//	EXPECT_THROW(board.move(piece3, { 4,3 }), ImpossibleMove);
//	board.verifieCheck(color2);
//
//	std::string color4 = COLORPLAYER1;
//	Position p4{ 8, 6 };
//	PiecePtr piece4(new Bishop{ p4,color4,&board });
//	board.addPiece(piece4);
//
//	EXPECT_THROW(board.move(piece4, { 7,7 }), Check);
//}

TEST(Board, too_many_kings)
{
	Board board{ Empty{} };


	Position  kingPosition1{ 4,4 };	
	std::string color = COLORPLAYER1;
	PiecePtr  king(new King{ kingPosition1,color,&board });

	board.addPiece(king);

	EXPECT_THROW(board.move(king, {4,5}), NotTwoKings);

	Position  kingPosition2{ 5,6 };
	std::string color2 = COLORPLAYER1;
	PiecePtr  king2(new King{ kingPosition2,color2,&board });

	Position  kingPosition3{ 3,3 };
	std::string color3 = COLORPLAYER2;
	PiecePtr  king3(new King{ kingPosition3,color3,&board });

	EXPECT_THROW(board.addPiece(king2), NotTwoKings);
	board.addPiece(king3);
	EXPECT_THROW(board.addPiece(king), NotTwoKings);

}



TEST(Pawn, moves)
{
	Board board{};

	PiecePtr pawn = board.getPiece({ 2,2 });
	std::vector<Position> expected =
	{
		{2,3},
		{2,4}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = pawn->getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected, gotten);

	PiecePtr pawn2 = board.getPiece({ 3,7 });
	std::vector<Position> expected2 =
	{
		{3,6},
		{3,5}
	};
	std::sort(expected2.begin(), expected2.end());
	std::vector<Position> gotten2 = pawn2->getMoves();
	std::sort(gotten2.begin(), gotten2.end());
	EXPECT_EQ(expected2, gotten2);

	board.move(pawn, { 2,4 });
	board.move(pawn, { 2,5 });
	board.move(pawn2, { 3,6 });

	std::vector<Position> expected3 =
	{
		{2,6},
		{3,6}
	};
	std::sort(expected3.begin(), expected3.end());
	std::vector<Position> gotten3 = pawn->getMoves();
	std::sort(gotten3.begin(), gotten3.end());
	EXPECT_EQ(expected3, gotten3);

	std::vector<Position> expected4 =
	{
		{3,5},
		{2,5}
	};
	std::sort(expected4.begin(), expected4.end());
	std::vector<Position> gotten4 = pawn2->getMoves();
	std::sort(gotten4.begin(), gotten4.end());
	EXPECT_EQ(expected4, gotten4);

	PiecePtr bishop = board.getPiece({ 3,1 });
	board.move(bishop, { 1, 3 });

	std::vector<Position> expected5 =
	{};
	std::sort(expected5.begin(), expected5.end());
	std::vector<Position> gotten5 = board.getPiece({1,2})->getMoves();
	std::sort(gotten5.begin(), gotten5.end());
	EXPECT_EQ(expected5, gotten5);

}
//
//TEST(Pawn, promotion)
//{
//	Board board{ KingOnly{} };
//
//	std::string color = COLORPLAYER1;
//	Position pawnPosition{ 7, 7 };
//	PiecePtr pawn(new Pawn{pawnPosition,color,&board });
//
//	EXPECT_THROW(board.move(pawn, {7,8}),Promotion);
//
//}

TEST(Board, castleling)
{
	//small castle
	Board board1{};
	PiecePtr king = board1.getPiece({5, 1});

	//piece in the middle
	std::vector<Position> expected6 =
	{};
	std::sort(expected6.begin(), expected6.end());
	std::vector<Position> gotten6 = king->getMoves();
	std::sort(gotten6.begin(), gotten6.end());
	EXPECT_EQ(expected6, gotten6);

	PiecePtr rightKnight = board1.getPiece({7,1});
	board1.move(rightKnight, {8,3});
	PiecePtr pawn = board1.getPiece({5,2});
	board1.move(pawn, { 5,4 });



	std::vector<Position> expected =
	{
		{5,2}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = king->getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected, gotten);

	PiecePtr bishop = board1.getPiece({6,1});
	board1.move(bishop, { 3,4 });

	std::vector<Position> expected2 =
	{
		{5,2},
		{6,1},
		{7,1}
	};
	std::sort(expected2.begin(), expected2.end());
	std::vector<Position> gotten2 = king->getMoves();
	std::sort(gotten2.begin(), gotten2.end());
	EXPECT_EQ(expected2, gotten2);

	board1.move(king, { 7,1 });
	PiecePtr kingShouldBeHere = board1.getPiece({7,1});
	PiecePtr rookShouldBeHere = board1.getPiece({6,1});
	EXPECT_TRUE((dynamic_cast<King*>(kingShouldBeHere.get()) && dynamic_cast<Rook*>(rookShouldBeHere.get())));


	//scenario check in the middle 
	PiecePtr pawn2 = board1.getPiece({6,7});
	board1.move(pawn2, {6,5});
	PiecePtr pawn3 = board1.getPiece({ 5,7 });
	board1.move(pawn3, { 5,5 });
	PiecePtr bishop2 = board1.getPiece({6,8});
	board1.move(bishop2, {1,3});
	PiecePtr kinght2 = board1.getPiece({7,8});
	board1.move(kinght2, {8,6});

	PiecePtr king2 = board1.getPiece({5,8});
	std::vector<Position> expected3 =
	{
		{5,7},
		{6,7},
		{6,8}
	};
	std::sort(expected3.begin(), expected3.end());
	std::vector<Position> gotten3 = king2->getMoves();
	std::sort(gotten3.begin(), gotten3.end());
	EXPECT_EQ(expected3, gotten3);

	//big castle
	PiecePtr knight3 = board1.getPiece({2,8});
	board1.move(knight3, {1,6});
	PiecePtr queen2 = board1.getPiece({4,8});
	board1.move(queen2, {8,4});
	PiecePtr pawn4 = board1.getPiece({2,7});
	board1.move(pawn4, {2,6});
	PiecePtr bishop3 = board1.getPiece({3,8});
	board1.move(bishop3, {2,7});

	std::vector<Position> expected4 =
	{
		{5,7},
		{6,7},
		{6,8},
		{4,8},
		{3,8}
	};
	std::sort(expected4.begin(), expected4.end());
	std::vector<Position> gotten4 = king2->getMoves();
	std::sort(gotten4.begin(), gotten4.end());
	EXPECT_EQ(expected4, gotten4);

	board1.move(king2, { 3,8 });
	PiecePtr kingShouldBeHere2 = board1.getPiece({ 3,8 });
	PiecePtr rookShouldBeHere2 = board1.getPiece({ 4,8 });
	EXPECT_TRUE((dynamic_cast<King*>(kingShouldBeHere2.get()) && dynamic_cast<Rook*>(rookShouldBeHere2.get())));


	Board board2{};
	PiecePtr pawn11 = board2.getPiece({5,2});
	board2.move(pawn11, { 5,4 });
	PiecePtr king11 = board2.getPiece({5,1});
	board2.move(king11, {5,2});

	//scenario king as move
	auto kingPtr = dynamic_cast<King*>(king11.get());
	EXPECT_FALSE(kingPtr->canSmallCastle() || kingPtr->canBigCastle() );


	//scenario rook as move
	PiecePtr pawn22 = board2.getPiece({8,7});
	board2.move(pawn22, { 8,5 });
	PiecePtr rook22 = board2.getPiece({8,8});
	board2.move(rook22, {8,7});

	PiecePtr king22 = board2.getPiece({5,8});

	auto kingPtr2 = dynamic_cast<King*>(king22.get());
	EXPECT_FALSE(kingPtr2->canSmallCastle());

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
	Position  kingPosition1{ 1,4 };
	PiecePtr  king1(new King{ kingPosition1,color,game.getBoard() });

	Position  rookPosition1{ 7,1 };
	PiecePtr  rook1(new Rook{ rookPosition1,color,game.getBoard() });

	color = COLORPLAYER2;
	Position  kingPosition2{ 8,7 };
	PiecePtr  king2(new King{ kingPosition2,color,game.getBoard() });

	Position  pawnPosition1{ 7,6 };
	PiecePtr  pawn1(new Pawn{ pawnPosition1,color,game.getBoard() });

	Position  pawnPosition2{ 7,7 };
	PiecePtr  pawn2(new Pawn{ pawnPosition2,color,game.getBoard() });

	Position  pawnPosition3{ 7,8 };
	PiecePtr  pawn3(new Pawn{ pawnPosition3,color,game.getBoard() });

	game.getBoard()->addPiece(king1);
	game.getBoard()->addPiece(rook1);
	game.getBoard()->addPiece(king2);
	game.getBoard()->addPiece(pawn1);
	game.getBoard()->addPiece(pawn2);
	game.getBoard()->addPiece(pawn3);

	Position to{ 8, 1 };
	EXPECT_TRUE(game.isValidMove(rookPosition1, to));

	//test1 isEnded()
	EXPECT_FALSE(game.isEnded());

	//test2 isEnded()
	game.getBoard()->move(rook1, to);
	EXPECT_TRUE(game.isEnded());
}

TEST(Game, getPieceEat) {
	Game game{};
	std::string color = COLORPLAYER1;
	Position  kingPosition1{ 1,4 };
	PiecePtr  king1(new King{ kingPosition1,color,game.getBoard() });

	Position knightPosition1{ 4, 4 };
	PiecePtr knight1(new Knight{ knightPosition1, color, game.getBoard() });

	Position pawnPosition1{ 4, 1 };
	PiecePtr pawn1(new Pawn{ pawnPosition1, color, game.getBoard() });

	color = COLORPLAYER2;
	Position kingPosition2{ 8, 4 };
	PiecePtr king2(new King{ kingPosition2, color, game.getBoard() });

	Position bishopPosition2{ 5, 2 };
	PiecePtr bishop2(new Bishop{ bishopPosition2, color, game.getBoard() });

	Position pawnPosition2{ 6, 1 };
	PiecePtr pawn2(new Pawn{ pawnPosition2, color, game.getBoard() });

	game.getBoard()->addPiece(king1);
	game.getBoard()->addPiece(knight1);
	game.getBoard()->addPiece(pawn1);
	game.getBoard()->addPiece(king2);
	game.getBoard()->addPiece(bishop2);
	game.getBoard()->addPiece(pawn2);

	std::set<PiecePtr> eatenPiecesExpected = {};
	EXPECT_TRUE(game.getPieceEat() == eatenPiecesExpected);

	game.getBoard()->move(knight1, bishopPosition2);
	game.getBoard()->move(pawn2, bishopPosition2);
	game.getBoard()->move(pawn1, bishopPosition2);

	eatenPiecesExpected.insert(bishop2);
	eatenPiecesExpected.insert(knight1);
	eatenPiecesExpected.insert(pawn2);
	EXPECT_TRUE(game.getPieceEat() == eatenPiecesExpected);

}

TEST(Game, starts) {}
TEST(Game, undo_redo) {}

TEST(Game, checkMate) {}
TEST(Game, check) {}//maybe checkmate va le cover
TEST(Game, getAllPossibleMoves) {}

TEST(Game, setter) {}
TEST(Game, move) {}







#endif
