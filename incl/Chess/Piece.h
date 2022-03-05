#pragma once


// Ids
enum Piece {
	None = 0,
	WPawn,
	WKnight,
	WBishop,
	WRook,
	WQueen,
	WKing,
	BPawn,
	BKnight,
	BBishop,
	BRook,
	BQueen,
	BKing,
};


// Returns piece type
int PieceType(Piece piece);
