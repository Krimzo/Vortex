#pragma once

#include "KrimzLib/KrimzLib.hpp"

#include "Chess/Piece.h"
#include "Chess/BoardState.h"


class Board {
public:
	// Icons
	static const kl::image icons[16];

	// Colors
	static kl::color squareL;
	static kl::color squareD;
	static kl::color selectL;
	static kl::color selectD;
	static kl::color lastL;
	static kl::color lastD;
	static kl::color wonL;
	static kl::color wonD;

	// Piece
	int selecSqr = -1;
	int wonSqr = -1;
	Move lastMove;

	// Rules
	bool whiteToPlay = true;
	bool wCanCastleK = true;
	bool wCanCastleQ = true;
	bool bCanCastleK = true;
	bool bCanCastleQ = true;

public:
	std::vector<Piece> pieces;
	std::vector<Move> moves;

	Board();

	// Clears the board
	void clear();

	// Loads fen data
	static const std::string defaultFen;
	void loadFen(const std::string& fen);

	// Returns possible moves of a piece
	std::vector<Move> getMoves(int pos) const;

	// Plays the move
	void playMove(const Move& move);

	// Logic and input
	void update(kl::window& win, kl::image& target);

	// Draws the board
	void draw(kl::image& target) const;
};
