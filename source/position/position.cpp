#include "position/position.h"


bool in_board(const int x, const int y)
{
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int get_index(const int x, const int y) {
	return y * 8 + x;
}


position::position()
{}

position::position(const fen& fen)
{
	load_fen(fen);
}

void position::load_fen(const fen& fen)
{
	const std::vector<std::string> parts = kl::strings::split(fen, ' ');
	if (kl::warning(parts.size() < 3, "Bad FEN data")) {
		return;
	}

	this->clear();

	white_to_play = (parts[1] == "w");

	for (int i = 0, position = 0; i < static_cast<int>(parts[0].size()) && position < 64; i++) {
		if (const char lower_char = static_cast<char>(tolower(fen[i])); lower_char == 'p' || lower_char == 'n' || lower_char == 'b' ||
			lower_char == 'r' || lower_char == 'q' || lower_char == 'k') {
			pieces[position++] = piece(static_cast<piece_type>(fen[i]));
		}
		else if (isdigit(fen[i])) {
			position += fen[i] - 48;
		}
	}

	for (const char c : parts[2]) {
		switch (c) {
		case 'K':
			castling_wk = true;
			break;
		case 'Q':
			castling_wq = true;
			break;
		case 'k':
			castling_bk = true;
			break;
		case 'q':
			castling_bq = true;
			break;
		}
	}
}

void position::clear()
{
	evaluation = 0;
	for (auto& piece : pieces) {
		piece = {};
	}
	
	white_to_play = true;
	castling_wk = true;
	castling_wq = true;
	castling_bk = true;
	castling_bq = true;

	last_played_move = kl::int2::splash(-1);
}

position position::after_playing(const int from_index, const int to_index, const piece_type new_type) const {
	position position = *this;

	if (position.pieces[from_index].type == w_king) {
		position.castling_wk = false;
		position.castling_wq = false;
	}

	if (position.pieces[from_index].type == b_king) {
		position.castling_bk = false;
		position.castling_bq = false;
	}

	if (position.pieces[from_index].type == w_rook) {
		if (from_index == 63) {
			position.castling_wk = false;
		}
		else if (from_index == 56) {
			position.castling_wq = false;
		}
	}

	if (position.pieces[from_index].type == b_rook) {
		if (from_index == 7) {
			position.castling_bk = false;
		}
		else if (from_index == 0) {
			position.castling_bq = false;
		}
	}

	position.last_played_move.x = from_index;
	position.last_played_move.y = to_index;

	position.pieces[from_index].type = none;
	position.pieces[to_index].type = new_type;

	position.white_to_play = !white_to_play;

	return position;
}

int position::get_win_state() const
{
	int white_king_count = 0;
	int black_king_count = 0;

	for (auto& piece : pieces) {
		if (piece.type == w_king) {
			white_king_count += 1;
		}
		if (piece.type == b_king) {
			black_king_count += 1;
		}
	}

	return white_king_count - black_king_count;
}
