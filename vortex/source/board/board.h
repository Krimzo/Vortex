#pragma once

#include "board/piece.h"


namespace vtx {
	inline constexpr const char* default_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";
}

namespace vtx {
	bool in_board(int x, int y);
	int get_index(int x, int y);
}

namespace vtx {
	struct Board
	{
		Piece pieces[8 * 8] = {};

		float evaluation = 0.0f;

		int8_t selected_square = -1;
		int8_t last_played_from = -1;
		int8_t last_played_to = -1;

		bool white_to_play : 1 = true;
		bool castling_wk : 1 = true;
		bool castling_wq : 1 = true;
		bool castling_bk : 1 = true;
		bool castling_bq : 1 = true;

		Board() = default;
		Board(const std::string_view& fen);

		Piece& operator[](int index);
		const Piece& operator[](int index) const;

		Piece& operator()(int x, int y);
		const Piece& operator()(int x, int y) const;
		
		void load_fen(const std::string_view& fen);
		void reset();

		Board after_playing(int from_index, int to_index, char new_type) const;
		int get_win_state() const;
	};
}
