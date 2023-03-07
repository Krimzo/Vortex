#include "moves/moves.h"


void vtx::get_white_knight_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	if (in_board(x + 1, y + 2) && board[get_index(x + 1, y + 2)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y + 2), w_knight));
	if (in_board(x - 1, y + 2) && board[get_index(x - 1, y + 2)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y + 2), w_knight));
	if (in_board(x + 1, y - 2) && board[get_index(x + 1, y - 2)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y - 2), w_knight));
	if (in_board(x - 1, y - 2) && board[get_index(x - 1, y - 2)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y - 2), w_knight));
	if (in_board(x + 2, y + 1) && board[get_index(x + 2, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 2, y + 1), w_knight));
	if (in_board(x + 2, y - 1) && board[get_index(x + 2, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 2, y - 1), w_knight));
	if (in_board(x - 2, y + 1) && board[get_index(x - 2, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 2, y + 1), w_knight));
	if (in_board(x - 2, y - 1) && board[get_index(x - 2, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 2, y - 1), w_knight));
}

void vtx::get_black_knight_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	if (in_board(x + 1, y + 2) && board[get_index(x + 1, y + 2)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y + 2), b_knight));
	if (in_board(x - 1, y + 2) && board[get_index(x - 1, y + 2)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y + 2), b_knight));
	if (in_board(x + 1, y - 2) && board[get_index(x + 1, y - 2)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 1, y - 2), b_knight));
	if (in_board(x - 1, y - 2) && board[get_index(x - 1, y - 2)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 1, y - 2), b_knight));
	if (in_board(x + 2, y + 1) && board[get_index(x + 2, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 2, y + 1), b_knight));
	if (in_board(x + 2, y - 1) && board[get_index(x + 2, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x + 2, y - 1), b_knight));
	if (in_board(x - 2, y + 1) && board[get_index(x - 2, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 2, y + 1), b_knight));
	if (in_board(x - 2, y - 1) && board[get_index(x - 2, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(get_index(x, y), get_index(x - 2, y - 1), b_knight));
}
