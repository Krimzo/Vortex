#pragma once

#include "klibrary.h"


namespace vtx {
	enum PieceType : int8_t
	{
		PIECE_NONE = 0,
		W_PAWN,
		W_KNIGHT,
		W_BISHOP,
		W_ROOK,
		W_QUEEN,
		W_KING,
		B_PAWN,
		B_KNIGHT,
		B_BISHOP,
		B_ROOK,
		B_QUEEN,
		B_KING,
		_PIECE_TYPE_COUNT,
	};
}

namespace vtx {
	constexpr PieceType char_to_piece(char c)
	{
		switch (c)
		{
		case 'P': return W_PAWN;
		case 'N': return W_KNIGHT;
		case 'B': return W_BISHOP;
		case 'R': return W_ROOK;
		case 'Q': return W_QUEEN;
		case 'K': return W_KING;
		case 'p': return B_PAWN;
		case 'n': return B_KNIGHT;
		case 'b': return B_BISHOP;
		case 'r': return B_ROOK;
		case 'q': return B_QUEEN;
		case 'k': return B_KING;
		default: return PIECE_NONE;
		}
	}
}

namespace vtx {
	struct Piece
	{
		PieceType type;

		constexpr Piece(PieceType type = PIECE_NONE)
			: type(type)
		{}

		constexpr operator bool() const
		{
			return type != PIECE_NONE;
		}

		constexpr bool is_white(bool allow_none = false) const
		{
			return (type >= W_PAWN && type <= W_KING) || (type == PIECE_NONE && allow_none);
		}

		constexpr bool is_black(bool allow_none = false) const
		{
            return (type >= B_PAWN && type <= B_KING) || (type == PIECE_NONE && allow_none);
		}
	};
}
