#pragma once

#include "klib.h"


namespace vtx {
	inline const char none = 0;

	inline const char w_pawn = 'P';
	inline const char w_knight = 'N';
	inline const char w_bishop = 'B';
	inline const char w_rook = 'R';
	inline const char w_queen = 'Q';
	inline const char w_king = 'K';

	inline const char b_pawn = 'p';
	inline const char b_knight = 'n';
	inline const char b_bishop = 'b';
	inline const char b_rook = 'r';
	inline const char b_queen = 'q';
	inline const char b_king = 'k';
}

namespace vtx {
	class piece
	{
	public:
		char type = none;

		piece();
		piece(char type);

		operator char() const;

		bool is_white(bool allow_none = false) const;
		bool is_black(bool allow_none = false) const;
	};
}
