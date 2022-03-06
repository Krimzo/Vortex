#pragma once

#include "KrimzLib/KrimzLib.hpp"


class Piece {
public:
	// Ids
	enum class Type {
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
		BKing
	};

public:
	Piece::Type type;

	Piece();
	Piece(Piece::Type type);

	// Returns piece color
	int color() const;
};
