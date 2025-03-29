#include "vortex.h"


void vtx::get_white_knight_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	if (in_board(x + 1, y + 2) && board[get_index(x + 1, y + 2)].is_black(true))
	{
		board.after_playing(from_index, get_index(x + 1, y + 2), W_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 1, y + 2) && board[get_index(x - 1, y + 2)].is_black(true))
	{
		board.after_playing(from_index, get_index(x - 1, y + 2), W_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y - 2) && board[get_index(x + 1, y - 2)].is_black(true))
	{
		board.after_playing(from_index, get_index(x + 1, y - 2), W_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 1, y - 2) && board[get_index(x - 1, y - 2)].is_black(true))
	{
		board.after_playing(from_index, get_index(x - 1, y - 2), W_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 2, y + 1) && board[get_index(x + 2, y + 1)].is_black(true))
	{
		board.after_playing(from_index, get_index(x + 2, y + 1), W_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 2, y - 1) && board[get_index(x + 2, y - 1)].is_black(true))
	{
		board.after_playing(from_index, get_index(x + 2, y - 1), W_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 2, y + 1) && board[get_index(x - 2, y + 1)].is_black(true))
	{
		board.after_playing(from_index, get_index(x - 2, y + 1), W_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 2, y - 1) && board[get_index(x - 2, y - 1)].is_black(true))
	{
		board.after_playing(from_index, get_index(x - 2, y - 1), W_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
}

void vtx::get_black_knight_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	int from_index = get_index(x, y);
	Board temp_board;

	if (in_board(x + 1, y + 2) && board[get_index(x + 1, y + 2)].is_white(true))
	{
		board.after_playing(from_index, get_index(x + 1, y + 2), B_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 1, y + 2) && board[get_index(x - 1, y + 2)].is_white(true))
	{
		board.after_playing(from_index, get_index(x - 1, y + 2), B_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 1, y - 2) && board[get_index(x + 1, y - 2)].is_white(true))
	{
		board.after_playing(from_index, get_index(x + 1, y - 2), B_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 1, y - 2) && board[get_index(x - 1, y - 2)].is_white(true))
	{
		board.after_playing(from_index, get_index(x - 1, y - 2), B_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 2, y + 1) && board[get_index(x + 2, y + 1)].is_white(true))
	{
		board.after_playing(from_index, get_index(x + 2, y + 1), B_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x + 2, y - 1) && board[get_index(x + 2, y - 1)].is_white(true))
	{
		board.after_playing(from_index, get_index(x + 2, y - 1), B_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 2, y + 1) && board[get_index(x - 2, y + 1)].is_white(true))
	{
		board.after_playing(from_index, get_index(x - 2, y + 1), B_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
	if (in_board(x - 2, y - 1) && board[get_index(x - 2, y - 1)].is_white(true))
	{
		board.after_playing(from_index, get_index(x - 2, y - 1), B_KNIGHT, temp_board);
		board_iterator(temp_board);
	}
}
