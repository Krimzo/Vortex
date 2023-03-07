#include "moves/moves.h"


void vtx::get_white_king_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	if (in_board(x - 1, y + 1) && board[get_index(x - 1, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y + 1), w_king));
	if (in_board(x + 0, y + 1) && board[get_index(x + 0, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 0, y + 1), w_king));
	if (in_board(x + 1, y + 1) && board[get_index(x + 1, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y + 1), w_king));
	if (in_board(x + 1, y + 0) && board[get_index(x + 1, y + 0)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y + 0), w_king));
	if (in_board(x + 1, y - 1) && board[get_index(x + 1, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y - 1), w_king));
	if (in_board(x + 0, y - 1) && board[get_index(x + 0, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 0, y - 1), w_king));
	if (in_board(x - 1, y - 1) && board[get_index(x - 1, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y - 1), w_king));
	if (in_board(x - 1, y + 0) && board[get_index(x - 1, y + 0)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y + 0), w_king));

	if (board.castling_wk && !board[61] && !board[62]) {
		vtx::board new_board = board.after_playing(60, 62, w_king);
		new_board[63].type = none;
		new_board[61].type = w_rook;
		out_boards.push_back(new_board);
	}
	if (board.castling_wq && !board[57] && !board[58] && !board[59]) {
		vtx::board new_board = board.after_playing(60, 58, w_king);
		new_board[56].type = none;
		new_board[59].type = w_rook;
		out_boards.push_back(new_board);
	}
}

void vtx::get_black_king_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	if (in_board(x - 1, y + 1) && board[get_index(x - 1, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y + 1), b_king));
	if (in_board(x + 0, y + 1) && board[get_index(x + 0, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 0, y + 1), b_king));
	if (in_board(x + 1, y + 1) && board[get_index(x + 1, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y + 1), b_king));
	if (in_board(x + 1, y + 0) && board[get_index(x + 1, y + 0)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y + 0), b_king));
	if (in_board(x + 1, y - 1) && board[get_index(x + 1, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y - 1), b_king));
	if (in_board(x + 0, y - 1) && board[get_index(x + 0, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 0, y - 1), b_king));
	if (in_board(x - 1, y - 1) && board[get_index(x - 1, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y - 1), b_king));
	if (in_board(x - 1, y + 0) && board[get_index(x - 1, y + 0)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y + 0), b_king));

	if (board.castling_bk && !board[5] && !board[6]) {
		vtx::board new_board = board.after_playing(4, 6, b_king);
		new_board[7].type = none;
		new_board[5].type = b_rook;
		out_boards.push_back(new_board);
	}
	if (board.castling_bq && !board[1] && !board[2] && !board[3]) {
		vtx::board new_board = board.after_playing(4, 2, b_king);
		new_board[0].type = none;
		new_board[3].type = b_rook;
		out_boards.push_back(new_board);
	}
}
