#include "vortex.h"


void vtx::get_white_pawn_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	if (in_board(x, y - 1) && !board[get_index(x, y - 1)]) {
		board.after_playing(from_index, get_index(x, y - 1), (y == 1) ? W_QUEEN : W_PAWN, temp_board);
		board_iterator(temp_board);

		if (y == 6 && !board[get_index(x, y - 2)]) {
			board.after_playing(from_index, get_index(x, y - 2), W_PAWN, temp_board);
			board_iterator(temp_board);
		}
	}

	if (in_board(x - 1, y - 1) && board[get_index(x - 1, y - 1)].is_black()) {
		board.after_playing(from_index, get_index(x - 1, y - 1), (y == 1) ? W_QUEEN : W_PAWN, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y - 1) && board[get_index(x + 1, y - 1)].is_black()) {
		board.after_playing(from_index, get_index(x + 1, y - 1), (y == 1) ? W_QUEEN : W_PAWN, temp_board);
		board_iterator(temp_board);
	}
}

void vtx::get_black_pawn_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	if (in_board(x, y + 1) && !board[get_index(x, y + 1)]) {
		board.after_playing(from_index, get_index(x, y + 1), (y == 6) ? B_QUEEN : B_PAWN, temp_board);
		board_iterator(temp_board);

		if (y == 1 && !board[get_index(x, y + 2)]) {
			board.after_playing(from_index, get_index(x, y + 2), B_PAWN, temp_board);
			board_iterator(temp_board);
		}
	}

	if (in_board(x - 1, y + 1) && board[get_index(x - 1, y + 1)].is_white()) {
		board.after_playing(from_index, get_index(x - 1, y + 1), (y == 6) ? B_QUEEN : B_PAWN, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y + 1) && board[get_index(x + 1, y + 1)].is_white()) {
		board.after_playing(from_index, get_index(x + 1, y + 1), (y == 6) ? B_QUEEN : B_PAWN, temp_board);
		board_iterator(temp_board);
	}
}
