#include "moves/moves.h"


void vtx::get_white_rook_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y);
		if (in_board(x + i, y)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_rook));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_rook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y);
		if (in_board(x - i, y)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_rook));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_rook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x, y + i);
		if (in_board(x, y + i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_rook));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_rook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x, y - i);
		if (in_board(x, y - i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_rook));
			}
			else if (board[index].is_black()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, w_rook));
				break;
			}
			else {
				break;
			}
		}
	}
}

void vtx::get_black_rook_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y);
		if (in_board(x + i, y)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_rook));
			}
			else if (board[index].is_white()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_rook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y);
		if (in_board(x - i, y)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_rook));
			}
			else if (board[index].is_white()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_rook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x, y + i);
		if (in_board(x, y + i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_rook));
			}
			else if (board[index].is_white()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_rook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x, y - i);
		if (in_board(x, y - i)) {
			if (!board[index]) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_rook));
			}
			else if (board[index].is_white()) {
				out_boards.push_back(board.after_playing(get_index(x, y), index, b_rook));
				break;
			}
			else {
				break;
			}
		}
	}
}
