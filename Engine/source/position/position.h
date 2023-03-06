#pragma once

#include "piece/piece.h"


using fen = std::string;
inline const fen default_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";

bool in_board(int x, int y);

int get_index(int x, int y);

class position
{
public:
	piece pieces[64] = {};
	bool white_to_play = true;
	
	bool castling_wk = true;
	bool castling_wq = true;
	bool castling_bk = true;
	bool castling_bq = true;

	float evaluation = 0;
	kl::int2 last_played_move = kl::int2(-1);

	position();

	explicit position(const fen& fen);

	void load_fen(const fen& fen);

	void clear();

	[[nodiscard]] position after_playing(int from_index, int to_index, piece_type new_type) const;

	[[nodiscard]] int get_win_state() const;
};
