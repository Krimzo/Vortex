#include "moves/moves.h"


void vtx::get_white_queen_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	std::vector<vtx::board> bishop_boards = {};
	get_white_bishop_moves(board, x, y, bishop_boards);

	for (auto& new_board : bishop_boards) {
		new_board.pieces[new_board.last_played_move.y].type = w_queen;
		out_boards.push_back(new_board);
	}

	std::vector<vtx::board> rook_boards = {};
	get_white_rook_moves(board, x, y, rook_boards);

	for (auto& new_board : rook_boards) {
		new_board.pieces[new_board.last_played_move.y].type = w_queen;
		out_boards.push_back(new_board);
	}
}

void vtx::get_black_queen_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	std::vector<vtx::board> bishop_boards = {};
	get_black_bishop_moves(board, x, y, bishop_boards);

	for (auto& new_board : bishop_boards) {
		new_board.pieces[new_board.last_played_move.y].type = b_queen;
		out_boards.push_back(new_board);
	}

	std::vector<vtx::board> rook_boards;
	get_black_rook_moves(board, x, y, rook_boards);

	for (auto& new_board : rook_boards) {
		new_board.pieces[new_board.last_played_move.y].type = b_queen;
		out_boards.push_back(new_board);
	}
}
