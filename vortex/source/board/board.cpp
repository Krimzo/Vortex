#include "board/board.h"

#include "engine/engine.h"


// Helpers
bool vtx::in_board(const int x, const int y)
{
	return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

int vtx::get_index(const int x, const int y)
{
	return (x + y * 8);
}

// Board
vtx::board::board()
{}

vtx::board::board(const std::string& fen)
{
	load_fen(fen);
}

vtx::piece& vtx::board::operator[](const int index)
{
	return pieces[index];
}

const vtx::piece& vtx::board::operator[](const int index) const
{
	return pieces[index];
}

vtx::piece& vtx::board::operator()(const int x, const int y)
{
	return pieces[get_index(x, y)];
}

const vtx::piece& vtx::board::operator()(const int x, const int y) const
{
	return pieces[get_index(x, y)];
}

void vtx::board::load_fen(const std::string& fen)
{
	const std::vector<std::string> parts = kl::split_string(fen, ' ');
	if (kl::warning_check(parts.size() < 3, "Bad FEN data")) {
		return;
	}

	white_to_play = (parts[1] == "w");

	for (int i = 0, position = 0; i < int(parts[0].size()) && position < 64; i++) {
		if (const char lower_char = char(tolower(fen[i])); lower_char == 'p' || lower_char == 'n' || lower_char == 'b' ||
			lower_char == 'r' || lower_char == 'q' || lower_char == 'k') {
			pieces[position++] = piece(char(fen[i]));
		}
		else if (isdigit(fen[i])) {
			position += (fen[i] - 48);
		}
	}

	for (auto& c : parts[2]) {
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

void vtx::board::reset()
{
	for (auto& piece : pieces) {
		piece = none;
	}

	white_to_play = true;
	castling_wk = true;
	castling_wq = true;
	castling_bk = true;
	castling_bq = true;

	selected_square = -1;
	last_played_from = -1;
	last_played_to = -1;

	evaluation = 0.0f;
}

vtx::board vtx::board::after_playing(const int from_index, const int to_index, const char new_type) const {
	board board = *this;

	switch (board[from_index]) {
	case w_king:
		board.castling_wk = false;
		board.castling_wq = false;

	case b_king:
		board.castling_bk = false;
		board.castling_bq = false;

	case w_rook:
		if (from_index == 63) {
			board.castling_wk = false;
		}
		else if (from_index == 56) {
			board.castling_wq = false;
		}

	case b_rook:
		if (from_index == 7) {
			board.castling_bk = false;
		}
		else if (from_index == 0) {
			board.castling_bq = false;
		}
	}

	board.last_played_from = from_index;
	board.last_played_to = to_index;

	board[from_index].type = none;
	board[to_index].type = new_type;

	board.white_to_play = !white_to_play;
	return board;
}

int vtx::board::get_win_state() const
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

	return (white_king_count - black_king_count);
}
