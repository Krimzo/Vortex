#include "vortex.h"


void vtx::get_white_king_moves(const Board& board, const int x, const int y, std::vector<Board>& out_boards)
{
	const int from_index = get_index(x, y);

	if (in_board(x - 1, y + 1) && board[get_index(x - 1, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y + 1), W_KING));
	if (in_board(x + 0, y + 1) && board[get_index(x + 0, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 0, y + 1), W_KING));
	if (in_board(x + 1, y + 1) && board[get_index(x + 1, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y + 1), W_KING));
	if (in_board(x + 1, y + 0) && board[get_index(x + 1, y + 0)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y + 0), W_KING));
	if (in_board(x + 1, y - 1) && board[get_index(x + 1, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y - 1), W_KING));
	if (in_board(x + 0, y - 1) && board[get_index(x + 0, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 0, y - 1), W_KING));
	if (in_board(x - 1, y - 1) && board[get_index(x - 1, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y - 1), W_KING));
	if (in_board(x - 1, y + 0) && board[get_index(x - 1, y + 0)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y + 0), W_KING));

	if (board.castling_wk && !board[61] && !board[62]) {
		Board new_board = board.after_playing(60, 62, W_KING);
		new_board[63].type = PieceType::NONE;
		new_board[61].type = W_ROOK;
		out_boards.push_back(new_board);
	}
	if (board.castling_wq && !board[57] && !board[58] && !board[59]) {
		Board new_board = board.after_playing(60, 58, W_KING);
		new_board[56].type = PieceType::NONE;
		new_board[59].type = W_ROOK;
		out_boards.push_back(new_board);
	}
}

void vtx::get_black_king_moves(const Board& board, const int x, const int y, std::vector<Board>& out_boards)
{
	const int from_index = get_index(x, y);

	if (in_board(x - 1, y + 1) && board[get_index(x - 1, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y + 1), B_KING));
	if (in_board(x + 0, y + 1) && board[get_index(x + 0, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 0, y + 1), B_KING));
	if (in_board(x + 1, y + 1) && board[get_index(x + 1, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y + 1), B_KING));
	if (in_board(x + 1, y + 0) && board[get_index(x + 1, y + 0)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y + 0), B_KING));
	if (in_board(x + 1, y - 1) && board[get_index(x + 1, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y - 1), B_KING));
	if (in_board(x + 0, y - 1) && board[get_index(x + 0, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 0, y - 1), B_KING));
	if (in_board(x - 1, y - 1) && board[get_index(x - 1, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y - 1), B_KING));
	if (in_board(x - 1, y + 0) && board[get_index(x - 1, y + 0)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y + 0), B_KING));

	if (board.castling_bk && !board[5] && !board[6]) {
		Board new_board = board.after_playing(4, 6, B_KING);
		new_board[7].type = PieceType::NONE;
		new_board[5].type = B_ROOK;
		out_boards.push_back(new_board);
	}
	if (board.castling_bq && !board[1] && !board[2] && !board[3]) {
		Board new_board = board.after_playing(4, 2, B_KING);
		new_board[0].type = PieceType::NONE;
		new_board[3].type = B_ROOK;
		out_boards.push_back(new_board);
	}
}
