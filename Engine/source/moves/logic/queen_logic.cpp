#include "moves/moves.h"


void vtx::get_white_queen_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	std::vector<vtx::board> boards = {};
	boards.reserve(15);

	get_white_bishop_moves(board, x, y, boards);
	for (auto& new_board : boards) {
		new_board.pieces[new_board.last_played_to].type = w_queen;
		out_boards.push_back(new_board);
	}

	boards.clear();

	get_white_rook_moves(board, x, y, boards);
	for (auto& new_board : boards) {
		new_board.pieces[new_board.last_played_to].type = w_queen;
		out_boards.push_back(new_board);
	}
}

void vtx::get_black_queen_moves(const board& board, const int x, const int y, std::vector<vtx::board>& out_boards)
{
	std::vector<vtx::board> boards = {};
	boards.reserve(15);

	get_black_bishop_moves(board, x, y, boards);
	for (auto& new_board : boards) {
		new_board.pieces[new_board.last_played_to].type = b_queen;
		out_boards.push_back(new_board);
	}

	boards.clear();

	get_black_rook_moves(board, x, y, boards);
	for (auto& new_board : boards) {
		new_board.pieces[new_board.last_played_to].type = b_queen;
		out_boards.push_back(new_board);
	}
}
