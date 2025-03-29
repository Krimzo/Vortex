#include "vortex.h"


void vtx::get_white_bishop_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	// Top-Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y + i))
			break;

		int index = get_index(x + i, y + i);
		if (board[index].is_white())
			break;

		if (board[index].is_black()) {
			board.after_playing(from_index, index, W_BISHOP, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, W_BISHOP, temp_board);
		board_iterator(temp_board);
	}

	// Top-Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y + i))
			break;

		int index = get_index(x - i, y + i);
		if (board[index].is_white())
			break;

		if (board[index].is_black()) {
			board.after_playing(from_index, index, W_BISHOP, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, W_BISHOP, temp_board);
		board_iterator(temp_board);
	}

	// Bottom-Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y - i))
			break;

		int index = get_index(x + i, y - i);
		if (board[index].is_white())
			break;

		if (board[index].is_black()) {
			board.after_playing(from_index, index, W_BISHOP, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, W_BISHOP, temp_board);
		board_iterator(temp_board);
	}

	// Bottom-Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y - i))
			break;

		int index = get_index(x - i, y - i);
		if (board[index].is_white())
			break;

		if (board[index].is_black()) {
			board.after_playing(from_index, index, W_BISHOP, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, W_BISHOP, temp_board);
		board_iterator(temp_board);
	}
}

void vtx::get_black_bishop_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	// Top-Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y + i))
			break;

		int index = get_index(x + i, y + i);
		if (board[index].is_black())
			break;

		if (board[index].is_white()) {
			board.after_playing(from_index, index, B_BISHOP, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, B_BISHOP, temp_board);
		board_iterator(temp_board);
	}

	// Top-Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y + i))
			break;

		int index = get_index(x - i, y + i);
		if (board[index].is_black())
			break;

		if (board[index].is_white()) {
			board.after_playing(from_index, index, B_BISHOP, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, B_BISHOP, temp_board);
		board_iterator(temp_board);
	}

	// Bottom-Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y - i))
			break;

		int index = get_index(x + i, y - i);
		if (board[index].is_black())
			break;

		if (board[index].is_white()) {
			board.after_playing(from_index, index, B_BISHOP, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, B_BISHOP, temp_board);
		board_iterator(temp_board);
	}

	// Bottom-Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y - i))
			break;

		int index = get_index(x - i, y - i);
		if (board[index].is_black())
			break;

		if (board[index].is_white()) {
			board.after_playing(from_index, index, B_BISHOP, temp_board);
			board_iterator(temp_board);
			break;
		}

		board.after_playing(from_index, index, B_BISHOP, temp_board);
		board_iterator(temp_board);
	}
}
