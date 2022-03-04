#pragma once

#include "KrimzLib/KrimzLib.hpp"


// Piece ids
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

class Board {
public:
	// Piece icons
	static const kl::image icons[16];

public:
	// Board pieces
	Piece pieces[64] = {};

	// Colors
	kl::color squareL = kl::color(240, 215, 180);
	kl::color squareD = kl::color(180, 135, 100);
	kl::color selectL = kl::color(190, 190, 190);
	kl::color selectD = kl::color(145, 145, 145);

	// Render target
	kl::image* frame = nullptr;

	// Selected piece
	int selected = -1;

	// Board states
	bool whiteToPlay = true;

	// Castling rules
	bool wCanCastleK = true;
	bool wCanCastleQ = true;
	bool bCanCastleK = true;
	bool bCanCastleQ = true;

	// Loads fen data
	static const std::string defaultFen;
	void loadFen(const std::string& fen);

	// Draws the board
	void draw() const;
};
