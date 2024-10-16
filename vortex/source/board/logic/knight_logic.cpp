#include "vortex.h"


void vtx::get_white_knight_moves(const Board& board, const int x, const int y, std::vector<Board>& out_boards)
{
	const int from_index = get_index(x, y);

	if (in_board(x + 1, y + 2) && board[get_index(x + 1, y + 2)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y + 2), W_KNIGHT));
	if (in_board(x - 1, y + 2) && board[get_index(x - 1, y + 2)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y + 2), W_KNIGHT));
	if (in_board(x + 1, y - 2) && board[get_index(x + 1, y - 2)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y - 2), W_KNIGHT));
	if (in_board(x - 1, y - 2) && board[get_index(x - 1, y - 2)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y - 2), W_KNIGHT));
	if (in_board(x + 2, y + 1) && board[get_index(x + 2, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 2, y + 1), W_KNIGHT));
	if (in_board(x + 2, y - 1) && board[get_index(x + 2, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 2, y - 1), W_KNIGHT));
	if (in_board(x - 2, y + 1) && board[get_index(x - 2, y + 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 2, y + 1), W_KNIGHT));
	if (in_board(x - 2, y - 1) && board[get_index(x - 2, y - 1)].is_black(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 2, y - 1), W_KNIGHT));
}

void vtx::get_black_knight_moves(const Board& board, const int x, const int y, std::vector<Board>& out_boards)
{
	const int from_index = get_index(x, y);

	if (in_board(x + 1, y + 2) && board[get_index(x + 1, y + 2)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y + 2), B_KNIGHT));
	if (in_board(x - 1, y + 2) && board[get_index(x - 1, y + 2)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y + 2), B_KNIGHT));
	if (in_board(x + 1, y - 2) && board[get_index(x + 1, y - 2)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 1, y - 2), B_KNIGHT));
	if (in_board(x - 1, y - 2) && board[get_index(x - 1, y - 2)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 1, y - 2), B_KNIGHT));
	if (in_board(x + 2, y + 1) && board[get_index(x + 2, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 2, y + 1), B_KNIGHT));
	if (in_board(x + 2, y - 1) && board[get_index(x + 2, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x + 2, y - 1), B_KNIGHT));
	if (in_board(x - 2, y + 1) && board[get_index(x - 2, y + 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 2, y + 1), B_KNIGHT));
	if (in_board(x - 2, y - 1) && board[get_index(x - 2, y - 1)].is_white(true)) out_boards.push_back(board.after_playing(from_index, get_index(x - 2, y - 1), B_KNIGHT));
}
