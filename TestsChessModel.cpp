﻿#if __has_include("gtest/gtest.h")
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

#include "Pieces.h"
#include "Board.h"
#include "exepctions.h"




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
		"class ChessModel::Bishop 3, 1 bluelaite\n"
		"class ChessModel::Knight 7, 8 vertmoisi\n"
		"class ChessModel::Bishop 6, 1 bluelaite\n"
		"class ChessModel::Knight 2, 1 bluelaite\n"
		"class ChessModel::Bishop 3, 8 vertmoisi\n"
		"class ChessModel::Knight 7, 1 bluelaite\n"
		"class ChessModel::Bishop 6, 8 vertmoisi\n"
		"class ChessModel::King 4, 1 bluelaite\n"
		"class ChessModel::King 4, 8 vertmoisi\n";

	std::string text = buffer.str();
	// When done redirect cout to its old self
	std::cout.rdbuf(sbuf);

	EXPECT_EQ(text , expected);

}


TEST(Bishop, test_block_move) {

	Board board{};

	PiecePtr bishop = board.getPiece({ 3, 1 });
	board.move(bishop, { 4,2 });
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


TEST(King ,test_block_move) {


	Board board;
	std::string couleur = COLORPLAYER1;
	PiecePtr bishop = board.getPiece({ 3,1 });
	EXPECT_THROW(board.move(bishop, { 5,2 }), ImpossibleMove);
	board.move(bishop, { 4,2 });
	PiecePtr king = board.getPiece({ 4,1 });
	std::vector<Position> expected =
	{
		{3,1},
		//{4,2}, blocked by bishop
		{3,2},
		{5,1},
		{5,2},
	};

	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = king->getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);
}

TEST(Knight, test_block_move) {


	Board board;
	std::string couleur = COLORPLAYER1;
	PiecePtr bishop = board.getPiece({ 3,1 });
	EXPECT_THROW(board.move(bishop, { 5,2 }), ImpossibleMove);
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
		{3,2},
		{4,3},
		{6,3},
		{7,2}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = knigth.getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);
}


TEST(Bishop, moves) {

	Board board;
	Position position = { 5,1 };
	std::string couleur = COLORPLAYER1;
	Bishop bishop{ position,couleur,&board };
	std::vector<Position> expected =
	{
		{4,2},
		{3,3},
		{2,4},
		{1,5},
		{6,2},
		{7,3},
		{8,4}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = bishop.getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);
}


TEST(Bishop , block_move) {

	Board board;
	Position position = { 5,1 };
	std::string couleur = COLORPLAYER1;
	Bishop bishop{ position,couleur,&board };
	std::vector<Position> expected =
	{
		{4,2},
		{3,3},
		{2,4},
		{1,5},
		{6,2},
		{7,3},
		{8,4}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = bishop.getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);
}



TEST(Bishop, eat) {
	Board board;
	PiecePtr piece = board.getPiece({ 3,8 });
	EXPECT_THROW(board.move(piece, { 5,2 }), ImpossibleMove);
	board.move(piece, { 6,5 });

	Position posBishop1 = { 7 ,4 };
	std::string color1 = COLORPLAYER1;
	Bishop bishop1 = { posBishop1, color1, &board };

	std::vector<Position> expected =
	{
		{6, 5},
		{8, 5},
		{6, 3},
		{5, 2},
		{8, 3}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = bishop1.getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);

}


TEST(Knight, eat) {
	Board board;
	PiecePtr piece = board.getPiece({ 3,8 });
	EXPECT_THROW(board.move(piece, { 5,2 }), ImpossibleMove);
	board.move(piece, { 6,5 });

	Position posKnight1 = { 7 ,3 };
	std::string color1 = COLORPLAYER1;
	Knight bishop1 = { posKnight1, color1, &board };

	std::vector<Position> expected =
	{
		{6, 5},
		{8, 5},
		{5, 2},
		{5, 4},
		{8, 1}
	};
	std::sort(expected.begin(), expected.end());
	std::vector<Position> gotten = bishop1.getMoves();
	std::sort(gotten.begin(), gotten.end());
	EXPECT_EQ(expected , gotten);

}

TEST(Bishop, eaten) {
	Board board;
	PiecePtr bishopRight2 = board.getPiece({ 6,8 });

	board.move(bishopRight2, { 1,3 });

	PiecePtr bishopLeft1 = board.getPiece({ 3,1 });
	PiecePtr eatenPiece = board.move(bishopLeft1, { 1,3 });
	EXPECT_EQ(bishopRight2.get() , eatenPiece.get());
}

TEST(Bishop, piece_remove) {
	Board board;
	PiecePtr bishopRight2 = board.getPiece({ 6,8 });

	board.move(bishopRight2, { 1,3 });

	PiecePtr bishopLeft1 = board.getPiece({ 3,1 });
	PiecePtr eatenPiece = board.move(bishopLeft1, { 1,3 });
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
		"class ChessModel::Knight 7, 8 vertmoisi\n"
		"class ChessModel::Bishop 6, 1 bluelaite\n"
		"class ChessModel::Knight 2, 1 bluelaite\n"
		"class ChessModel::Bishop 3, 8 vertmoisi\n"
		"class ChessModel::Knight 7, 1 bluelaite\n"
		"class ChessModel::King 4, 1 bluelaite\n"
		"class ChessModel::King 4, 8 vertmoisi\n"
		"class ChessModel::Bishop 1, 3 bluelaite\n";

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


TEST(Board , checking)
{
	Board board{ Empty{} };


	std::string color1 = COLORPLAYER1;
	Position p1{ 4, 4 };
	PiecePtr piece1(new Bishop{ p1,color1,&board });
	board.addPiece(piece1);

	std::string color2 = COLORPLAYER2;
	Position p2{ 6, 6 };
	PiecePtr piece2(new King{ p2,color2,&board });
	board.addPiece(piece2);

	std::string colorking = COLORPLAYER1;
	Position pking{ 1, 1 };
	PiecePtr king(new King{ pking,colorking,&board });
	board.addPiece(king);

	EXPECT_THROW(board.verifieCheck(color2), Check);


	std::string color3 = COLORPLAYER2;
	Position p3{ 5, 5 };
	PiecePtr piece3(new Knight{ p3,color3,&board });
	board.addPiece(piece3);
	board.verifieCheck(color2);


	EXPECT_THROW(board.move(piece3, { 4,3 }), ImpossibleMove);
	board.verifieCheck(color2);

	std::string color4 = COLORPLAYER1;
	Position p4{ 8, 6 };
	PiecePtr piece4(new Bishop{ p4,color4,&board });
	board.addPiece(piece4);

	EXPECT_THROW(board.move(piece4, { 7,7 }), Check);
}

#endif