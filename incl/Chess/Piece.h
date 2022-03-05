#pragma once

#include "KrimzLib/KrimzLib.hpp"


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


// Returns piece color
int PieceColor(Piece piece);

// Returns possible moves
std::vector<int> PieceMoves(const std::vector<Piece>& pieces, int pos);
