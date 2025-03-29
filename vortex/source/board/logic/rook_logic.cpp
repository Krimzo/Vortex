#include "vortex.h"


void vtx::get_white_rook_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	// Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y))
			break;

		int index = get_index(x + i, y);
		if (board[index].is_white())
			break;

		if (board[index].is_black()) {
			board.after_playing(from_index, index, W_ROOK, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, W_ROOK, temp_board);
		board_iterator(temp_board);
	}

	// Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y))
			break;

		int index = get_index(x - i, y);
		if (board[index].is_white())
			break;

		if (board[index].is_black()) {
			board.after_playing(from_index, index, W_ROOK, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, W_ROOK, temp_board);
		board_iterator(temp_board);
	}

	// Top
	for (int i = 1; i < 8; i++) {
		if (!in_board(x, y + i))
			break;

		int index = get_index(x, y + i);
		if (board[index].is_white())
			break;

		if (board[index].is_black()) {
			board.after_playing(from_index, index, W_ROOK, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, W_ROOK, temp_board);
		board_iterator(temp_board);
	}

	// Bottom
	for (int i = 1; i < 8; i++) {
		if (!in_board(x, y - i))
			break;

		int index = get_index(x, y - i);
		if (board[index].is_white())
			break;
		
		if (board[index].is_black()) {
			board.after_playing(from_index, index, W_ROOK, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, W_ROOK, temp_board);
		board_iterator(temp_board);
	}
}

void vtx::get_black_rook_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	// Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y))
			break;

		int index = get_index(x + i, y);
		if (board[index].is_black())
			break;

		if (board[index].is_white()) {
			board.after_playing(from_index, index, B_ROOK, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, B_ROOK, temp_board);
		board_iterator(temp_board);
	}

	// Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y))
			break;

		int index = get_index(x - i, y);
		if (board[index].is_black())
			break;

		if (board[index].is_white()) {
			board.after_playing(from_index, index, B_ROOK, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, B_ROOK, temp_board);
		board_iterator(temp_board);
	}

	// Top
	for (int i = 1; i < 8; i++) {
		if (!in_board(x, y + i))
			break;

		int index = get_index(x, y + i);
		if (board[index].is_black())
			break;

		if (board[index].is_white()) {
			board.after_playing(from_index, index, B_ROOK, temp_board);
			break;
		}

		board.after_playing(from_index, index, B_ROOK, temp_board);
		board_iterator(temp_board);
	}

	// Bottom
	for (int i = 1; i < 8; i++) {
		if (!in_board(x, y - i))
			break;

		int index = get_index(x, y - i);
		if (board[index].is_black())
			break;

		if (board[index].is_white()) {
			board.after_playing(from_index, index, B_ROOK, temp_board);
			break;
		}

		board.after_playing(from_index, index, B_ROOK, temp_board);
		board_iterator(temp_board);
	}
}
