#pragma once

#include "klibrary.h"


namespace vtx {
	inline static constexpr char none = 0;

	inline static constexpr char w_pawn = 'P';
	inline static constexpr char w_knight = 'N';
	inline static constexpr char w_bishop = 'B';
	inline static constexpr char w_rook = 'R';
	inline static constexpr char w_queen = 'Q';
	inline static constexpr char w_king = 'K';

	inline static constexpr char b_pawn = 'p';
	inline static constexpr char b_knight = 'n';
	inline static constexpr char b_bishop = 'b';
	inline static constexpr char b_rook = 'r';
	inline static constexpr char b_queen = 'q';
	inline static constexpr char b_king = 'k';
}

namespace vtx {
	struct Piece
	{
		char type = none;

		Piece();
		Piece(char type);

		operator char() const;

		bool is_white(bool allow_none = false) const;
		bool is_black(bool allow_none = false) const;
	};
}
