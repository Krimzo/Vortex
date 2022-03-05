#pragma once

#include "KrimzLib/KrimzLib.hpp"

#include "Chess/Piece.h"


// Piece icons
inline const kl::image icons[16]{
	kl::image("res/w_pawn.png"),
	kl::image("res/w_knight.png"),
	kl::image("res/w_bishop.png"),
	kl::image("res/w_rook.png"),
	kl::image("res/w_queen.png"),
	kl::image("res/w_king.png"),
	kl::image("res/b_pawn.png"),
	kl::image("res/b_knight.png"),
	kl::image("res/b_bishop.png"),
	kl::image("res/b_rook.png"),
	kl::image("res/b_queen.png"),
	kl::image("res/b_king.png")
};

// Board pieces
inline Piece pieces[64] = {};

// Colors
inline kl::color squareL = kl::color(240, 215, 180);
inline kl::color squareD = kl::color(180, 135, 100);
inline kl::color selectL = kl::color(190, 190, 190);
inline kl::color selectD = kl::color(145, 145, 145);

// Render target
inline kl::image frame(kl::int2(800));

// Selected piece
inline int selected = -1;

// Board states
inline bool whiteToPlay = true;

// Castling rules
inline bool wCanCastleK = true;
inline bool wCanCastleQ = true;
inline bool bCanCastleK = true;
inline bool bCanCastleQ = true;

// Loads fen data
inline const std::string defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
void LoadFen(const std::string& fen);

// Draws the board
void DrawBoard();
