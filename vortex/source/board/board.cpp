#include "vortex.h"


vtx::Board::Board(std::string_view const& fen)
{
	load_fen(fen);
}

vtx::Piece& vtx::Board::operator[](int index)
{
	return pieces[index];
}

vtx::Piece const& vtx::Board::operator[](int index) const
{
	return pieces[index];
}

vtx::Piece& vtx::Board::operator()(int x, int y)
{
	return pieces[get_index(x, y)];
}

vtx::Piece const& vtx::Board::operator()(int x, int y) const
{
	return pieces[get_index(x, y)];
}

void vtx::Board::load_fen(std::string_view const& fen)
{
	std::vector<std::string> parts = kl::split_string(fen, ' ');
	if (parts.size() < 3)
		return;

	reset();
	white_to_play = (parts[1] == "w");

	for (int i = 0, position = 0; i < (int) parts[0].size() && position < 64; i++) {
		char lower_char = (char) tolower(fen[i]);
		if (lower_char == 'p' || lower_char == 'n' || lower_char == 'b' || lower_char == 'r' || lower_char == 'q' || lower_char == 'k') {
			pieces[position++] = Piece{ (PieceType) fen[i] };
		}
		else if (isdigit(fen[i])) {
			position += (fen[i] - 48);
		}
	}

	castling_wk = false;
	castling_wq = false;
	castling_bk = false;
	castling_bq = false;

	for (auto& c : parts[2]) {
		switch (c)
		{
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

void vtx::Board::reset()
{
	for (auto& piece : pieces)
		piece = PieceType::NONE;
	selected_square = -1;
	last_played_from = -1;
	last_played_to = -1;
	white_to_play = true;
	castling_wk = true;
	castling_wq = true;
	castling_bk = true;
	castling_bq = true;
}

void vtx::Board::after_playing(int from_index, int to_index, char new_type, Board& out) const
{
	out = *this;
	switch (out[from_index].type)
	{
	case W_KING:
		out.castling_wk = false;
		out.castling_wq = false;
		break;

	case B_KING:
		out.castling_bk = false;
		out.castling_bq = false;
		break;

	case W_ROOK:
		if (from_index == 63) {
			out.castling_wk = false;
		}
		else if (from_index == 56) {
			out.castling_wq = false;
		}
		break;

	case B_ROOK:
		if (from_index == 7) {
			out.castling_bk = false;
		}
		else if (from_index == 0) {
			out.castling_bq = false;
		}
		break;
	}
	out.last_played_from = from_index;
	out.last_played_to = to_index;
	out[from_index].type = PieceType::NONE;
	out[to_index].type = (PieceType) new_type;
	out.white_to_play = !white_to_play;
}

int vtx::Board::get_win_state() const
{
	int king_count = 0;
	for (auto& piece : pieces) {
		if (piece.type == W_KING) {
			king_count += 1;
		}
		else if (piece.type == B_KING) {
			king_count -= 1;
		}
	}
	return king_count;
}
