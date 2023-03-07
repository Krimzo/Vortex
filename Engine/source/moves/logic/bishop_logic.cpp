#include "moves/moves.h"


void vtx::get_white_bishop_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y + i);
		if (in_board(x + i, y + i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_bishop));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y + i);
		if (in_board(x - i, y + i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_bishop));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y - i);
		if (in_board(x + i, y - i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_bishop));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y - i);
		if (in_board(x - i, y - i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_bishop));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_bishop));
				break;
			}
			else {
				break;
			}
		}
	}
}

void vtx::get_black_bishop_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y + i);
		if (in_board(x + i, y + i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_bishop));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y + i);
		if (in_board(x - i, y + i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_bishop));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y - i);
		if (in_board(x + i, y - i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_bishop));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y - i);
		if (in_board(x - i, y - i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_bishop));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_bishop));
				break;
			}
			else {
				break;
			}
		}
	}
}
