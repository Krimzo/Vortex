#include "vortex.h"


void vtx::get_white_king_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	if (in_board(x - 1, y + 1) && board[get_index(x - 1, y + 1)].is_black(true)) {
		board.after_playing(from_index, get_index(x - 1, y + 1), W_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 0, y + 1) && board[get_index(x + 0, y + 1)].is_black(true)) {
		board.after_playing(from_index, get_index(x + 0, y + 1), W_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y + 1) && board[get_index(x + 1, y + 1)].is_black(true)) {
		board.after_playing(from_index, get_index(x + 1, y + 1), W_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y + 0) && board[get_index(x + 1, y + 0)].is_black(true)) {
		board.after_playing(from_index, get_index(x + 1, y + 0), W_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y - 1) && board[get_index(x + 1, y - 1)].is_black(true)) {
		board.after_playing(from_index, get_index(x + 1, y - 1), W_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 0, y - 1) && board[get_index(x + 0, y - 1)].is_black(true)) {
		board.after_playing(from_index, get_index(x + 0, y - 1), W_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 1, y - 1) && board[get_index(x - 1, y - 1)].is_black(true)) {
		board.after_playing(from_index, get_index(x - 1, y - 1), W_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 1, y + 0) && board[get_index(x - 1, y + 0)].is_black(true)) {
		board.after_playing(from_index, get_index(x - 1, y + 0), W_KING, temp_board);
		board_iterator(temp_board);
	}

	if (board.castling_wk && !board[61] && !board[62]) {
		board.after_playing(60, 62, W_KING, temp_board);
		temp_board[63].type = PieceType::NONE;
		temp_board[61].type = W_ROOK;
		board_iterator(temp_board);
	}
	if (board.castling_wq && !board[57] && !board[58] && !board[59]) {
		board.after_playing(60, 58, W_KING, temp_board);
		temp_board[56].type = PieceType::NONE;
		temp_board[59].type = W_ROOK;
		board_iterator(temp_board);
	}
}

void vtx::get_black_king_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	if (in_board(x - 1, y + 1) && board[get_index(x - 1, y + 1)].is_white(true)) {
		board.after_playing(from_index, get_index(x - 1, y + 1), B_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 0, y + 1) && board[get_index(x + 0, y + 1)].is_white(true)) {
		board.after_playing(from_index, get_index(x + 0, y + 1), B_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y + 1) && board[get_index(x + 1, y + 1)].is_white(true)) {
		board.after_playing(from_index, get_index(x + 1, y + 1), B_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y + 0) && board[get_index(x + 1, y + 0)].is_white(true)) {
		board.after_playing(from_index, get_index(x + 1, y + 0), B_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y - 1) && board[get_index(x + 1, y - 1)].is_white(true)) {
		board.after_playing(from_index, get_index(x + 1, y - 1), B_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 0, y - 1) && board[get_index(x + 0, y - 1)].is_white(true)) {
		board.after_playing(from_index, get_index(x + 0, y - 1), B_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 1, y - 1) && board[get_index(x - 1, y - 1)].is_white(true)) {
		board.after_playing(from_index, get_index(x - 1, y - 1), B_KING, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 1, y + 0) && board[get_index(x - 1, y + 0)].is_white(true)) {
		board.after_playing(from_index, get_index(x - 1, y + 0), B_KING, temp_board);
		board_iterator(temp_board);
	}

	if (board.castling_bk && !board[5] && !board[6]) {
		board.after_playing(4, 6, B_KING, temp_board);
		temp_board[7].type = PieceType::NONE;
		temp_board[5].type = B_ROOK;
		board_iterator(temp_board);
	}
	if (board.castling_bq && !board[1] && !board[2] && !board[3]) {
		board.after_playing(4, 2, B_KING, temp_board);
		temp_board[0].type = PieceType::NONE;
		temp_board[3].type = B_ROOK;
		board_iterator(temp_board);
	}
}
