#include "vortex.h"


bool vtx::in_board(const int x, const int y)
{
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int vtx::get_index(const int x, const int y)
{
	return x + y * 8;
}

vtx::Board::Board(const std::string_view& fen)
{
	load_fen(fen);
}

vtx::Piece& vtx::Board::operator[](const int index)
{
	return pieces[index];
}

const vtx::Piece& vtx::Board::operator[](const int index) const
{
	return pieces[index];
}

vtx::Piece& vtx::Board::operator()(const int x, const int y)
{
	return pieces[get_index(x, y)];
}

const vtx::Piece& vtx::Board::operator()(const int x, const int y) const
{
	return pieces[get_index(x, y)];
}

void vtx::Board::load_fen(const std::string_view& fen)
{
	const std::vector<std::string> parts = kl::split_string(fen, ' ');
	if (!kl::verify(parts.size() == 3, "Bad FEN data"))
		return;

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

	evaluation = 0.0f;

	selected_square = -1;
	last_played_from = -1;
	last_played_to = -1;

	white_to_play = true;
	castling_wk = true;
	castling_wq = true;
	castling_bk = true;
	castling_bq = true;
}

vtx::Board vtx::Board::after_playing(const int from_index, const int to_index, const char new_type) const {
	Board board = *this;

	switch (board[from_index].type)
	{
	case W_KING:
		board.castling_wk = false;
		board.castling_wq = false;
		break;

	case B_KING:
		board.castling_bk = false;
		board.castling_bq = false;
		break;

	case W_ROOK:
		if (from_index == 63) {
			board.castling_wk = false;
		}
		else if (from_index == 56) {
			board.castling_wq = false;
		}
		break;

	case B_ROOK:
		if (from_index == 7) {
			board.castling_bk = false;
		}
		else if (from_index == 0) {
			board.castling_bq = false;
		}
		break;
	}

	board.last_played_from = from_index;
	board.last_played_to = to_index;

	board[from_index].type = PieceType::NONE;
	board[to_index].type = (PieceType) new_type;

	board.white_to_play = !white_to_play;
	return board;
}

int vtx::Board::get_win_state() const
{
	int white_king_count = 0;
	int black_king_count = 0;
	for (auto& piece : pieces) {
		if (piece.type == W_KING) {
			white_king_count += 1;
		}
		if (piece.type == B_KING) {
			black_king_count += 1;
		}
	}
	return white_king_count - black_king_count;
}
