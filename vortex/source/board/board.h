#pragma once

#include "board/piece.h"


namespace vtx {
	inline constexpr auto default_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";
}

namespace vtx {
	constexpr bool in_board(int x, int y)
	{
		return x >= 0 && x < 8 && y >= 0 && y < 8;
	}

	constexpr int get_index(int x, int y)
	{
		return x + y * 8;
	}
}

namespace vtx {
	struct Board
	{
		Piece pieces[8 * 8] = {};
		int8_t selected_square = -1;
		int8_t last_played_from = -1;
		int8_t last_played_to = -1;
		bool white_to_play : 1 = true;
		bool castling_wk : 1 = true;
		bool castling_wq : 1 = true;
		bool castling_bk : 1 = true;
		bool castling_bq : 1 = true;

		Board() = default;
		Board(std::string_view const& fen);

		Piece& operator[](int index);
		Piece const& operator[](int index) const;

		Piece& operator()(int x, int y);
		Piece const& operator()(int x, int y) const;
		
		void load_fen(std::string_view const& fen);
		void reset();

		void after_playing(int from_index, int to_index, char new_type, Board& out) const;
		int get_win_state() const;
	};
}
