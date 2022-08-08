#pragma once


enum class Piece {
	None = 0,

	WPawn = 1,
	WKnight = 3,
	WBishop = 4,
	WRook = 5,
	WQueen = 9,
	WKing = 1'000'000,

	BPawn = -1,
	BKnight = -3,
	BBishop = -4,
	BRook = -5,
	BQueen = -9,
	BKing = -1'000'000,
};

enum class Castling {
	None = 0,

	WK,
	WQ,
	BK,
	BQ
};

struct Square {
	int index = -1;
	Piece piece = Piece::None;
};

struct Move {
	Square from = {};
	Square to = {};
	Castling castling = {};
};

struct BoardInfo {
	float evaluation = 0.0f;
	Move bestMove = {};
};
