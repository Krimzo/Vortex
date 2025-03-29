#include "vortex.h"


void vtx::get_white_queen_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	get_white_bishop_moves(board, x, y, [&](Board& board)
		{
			board.pieces[board.last_played_to].type = W_QUEEN;
			board_iterator(board);
		});
	get_white_rook_moves(board, x, y, [&](Board& board)
		{
			board.pieces[board.last_played_to].type = W_QUEEN;
			board_iterator(board);
		});
}

void vtx::get_black_queen_moves(Board const& board, int x, int y, std::function<void(Board&)> const& board_iterator)
{
	get_black_bishop_moves(board, x, y, [&](Board& board)
		{
			board.pieces[board.last_played_to].type = B_QUEEN;
			board_iterator(board);
		});
	get_black_rook_moves(board, x, y, [&](Board& board)
		{
			board.pieces[board.last_played_to].type = B_QUEEN;
			board_iterator(board);
		});
}
