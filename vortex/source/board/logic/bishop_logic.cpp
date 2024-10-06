#include "vortex.h"


void vtx::get_white_bishop_moves(const Board& board, const int x, const int y, std::vector<Board>& out_boards)
{
	const int from_index = get_index(x, y);

	// Top-Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y + i)) {
			break;
		}

		const int index = get_index(x + i, y + i);

		if (board[index].is_white()) {
			break;
		}

		if (board[index].is_black()) {
			out_boards.push_back(board.after_playing(from_index, index, w_bishop));
			break;
		}

		out_boards.push_back(board.after_playing(from_index, index, w_bishop));
	}

	// Top-Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y + i)) {
			break;
		}

		const int index = get_index(x - i, y + i);

		if (board[index].is_white()) {
			break;
		}

		if (board[index].is_black()) {
			out_boards.push_back(board.after_playing(from_index, index, w_bishop));
			break;
		}

		out_boards.push_back(board.after_playing(from_index, index, w_bishop));
	}

	// Bottom-Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y - i)) {
			break;
		}

		const int index = get_index(x + i, y - i);

		if (board[index].is_white()) {
			break;
		}

		if (board[index].is_black()) {
			out_boards.push_back(board.after_playing(from_index, index, w_bishop));
			break;
		}

		out_boards.push_back(board.after_playing(from_index, index, w_bishop));
	}

	// Bottom-Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y - i)) {
			break;
		}

		const int index = get_index(x - i, y - i);

		if (board[index].is_white()) {
			break;
		}

		if (board[index].is_black()) {
			out_boards.push_back(board.after_playing(from_index, index, w_bishop));
			break;
		}

		out_boards.push_back(board.after_playing(from_index, index, w_bishop));
	}
}

void vtx::get_black_bishop_moves(const Board& board, const int x, const int y, std::vector<Board>& out_boards)
{
	const int from_index = get_index(x, y);

	// Top-Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y + i)) {
			break;
		}

		const int index = get_index(x + i, y + i);

		if (board[index].is_black()) {
			break;
		}

		if (board[index].is_white()) {
			out_boards.push_back(board.after_playing(from_index, index, b_bishop));
			break;
		}

		out_boards.push_back(board.after_playing(from_index, index, b_bishop));
	}

	// Top-Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y + i)) {
			break;
		}

		const int index = get_index(x - i, y + i);

		if (board[index].is_black()) {
			break;
		}

		if (board[index].is_white()) {
			out_boards.push_back(board.after_playing(from_index, index, b_bishop));
			break;
		}

		out_boards.push_back(board.after_playing(from_index, index, b_bishop));
	}

	// Bottom-Right
	for (int i = 1; i < 8; i++) {
		if (!in_board(x + i, y - i)) {
			break;
		}

		const int index = get_index(x + i, y - i);

		if (board[index].is_black()) {
			break;
		}

		if (board[index].is_white()) {
			out_boards.push_back(board.after_playing(from_index, index, b_bishop));
			break;
		}

		out_boards.push_back(board.after_playing(from_index, index, b_bishop));
	}

	// Bottom-Left
	for (int i = 1; i < 8; i++) {
		if (!in_board(x - i, y - i)) {
			break;
		}

		const int index = get_index(x - i, y - i);

		if (board[index].is_black()) {
			break;
		}

		if (board[index].is_white()) {
			out_boards.push_back(board.after_playing(from_index, index, b_bishop));
			break;
		}

		out_boards.push_back(board.after_playing(from_index, index, b_bishop));
	}
}
