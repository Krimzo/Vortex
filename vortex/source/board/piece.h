#pragma once

#include "klibrary.h"


namespace vtx {
	enum PieceType : int8_t
	{
		NONE = 0,
		W_PAWN = 'P',
		W_KNIGHT = 'N',
		W_BISHOP = 'B',
		W_ROOK = 'R',
		W_QUEEN = 'Q',
		W_KING = 'K',
		B_PAWN = 'p',
		B_KNIGHT = 'n',
		B_BISHOP = 'b',
		B_ROOK = 'r',
		B_QUEEN = 'q',
		B_KING = 'k',
	};
}

namespace vtx {
	struct Piece
	{
		PieceType type;

		constexpr Piece(PieceType type = PieceType::NONE)
			: type(type)
		{}

		constexpr operator bool() const
		{
			return type != PieceType::NONE;
		}

		constexpr bool is_white(bool allow_none = false) const
		{
			return (type > 64 && type < 91) || (allow_none && !type);
		}

		constexpr bool is_black(bool allow_none = false) const
		{
			return (type > 96 && type < 123) || (allow_none && !type);
		}
	};
}
