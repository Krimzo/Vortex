#include "moves/moves.h"


void vtx::get_piece_moves(const board& board, const int piece_index, std::vector<vtx::board>& out_boards)
{
	const int x = (piece_index % 8);
	const int y = (piece_index / 8);

	switch (board[piece_index]) {
	case w_pawn:
		get_white_pawn_moves(board, x, y, out_boards);
		break;

	case b_pawn:
		get_black_pawn_moves(board, x, y, out_boards);
		break;

	case w_knight:
		get_white_knight_moves(board, x, y, out_boards);
		break;

	case b_knight:
		get_black_knight_moves(board, x, y, out_boards);
		break;

	case w_bishop:
		get_white_bishop_moves(board, x, y, out_boards);
		break;

	case b_bishop:
		get_black_bishop_moves(board, x, y, out_boards);
		break;

	case w_rook:
		get_white_rook_moves(board, x, y, out_boards);
		break;

	case b_rook:
		get_black_rook_moves(board, x, y, out_boards);
		break;

	case w_queen:
		get_white_queen_moves(board, x, y, out_boards);
		break;

	case b_queen:
		get_black_queen_moves(board, x, y, out_boards);
		break;

	case w_king:
		get_white_king_moves(board, x, y, out_boards);
		break;

	case b_king:
		get_black_king_moves(board, x, y, out_boards);
		break;
	}
}
