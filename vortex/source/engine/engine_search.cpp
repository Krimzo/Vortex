#include "vortex.h"


static constexpr float INF = std::numeric_limits<float>::infinity();

vtx::SearchResult vtx::Engine::search(Board& board, const int max_depth)
{
	const uint64_t start_time = kl::time::now();
	SearchResult result;
	result.board = search_rec(board, max_depth, 0, -INF, INF);
	result.depth = max_depth;
	result.time = kl::time::calculate(start_time, kl::time::now());
	return result;
}

vtx::Board vtx::Engine::search_rec(Board& board, const int max_depth, const int depth, float alpha, float beta)
{
	board.evaluation = evaluate(board);
	if (depth > max_depth || board.evaluation < -1e4f || board.evaluation > 1e4f) {
		return board;
	}

	Board best_position{};
	best_position.evaluation = (board.white_to_play ? -INF : INF);

	std::vector<Board> possible_boards;
	possible_boards.reserve(50);
	
	for (int i = 0; i < 64; i++) {
		Piece piece = board[i];
		if (!piece_type_check(board, piece)) {
			continue;
		}

		possible_boards.clear();
		get_piece_moves(board, i, possible_boards);

		for (auto& possible_board : possible_boards) {
			possible_board.evaluation = search_rec(possible_board, max_depth, depth + 1, alpha, beta).evaluation;
			if (evaluation_check(board.white_to_play, alpha, beta, possible_board, best_position)) {
				return best_position;
			}
		}
	}
	return best_position;
}

bool vtx::Engine::piece_type_check(const Board& board, const Piece piece)
{
	if (board.white_to_play && !piece.is_white()) {
		return false;
	}
	if (!board.white_to_play && !piece.is_black()) {
		return false;
	}
	return true;
}

bool vtx::Engine::evaluation_check(const bool white_to_play, float& alpha, float& beta, const Board& possible_board, Board& best_board)
{
	if (white_to_play) {
		if (possible_board.evaluation > best_board.evaluation) {
			best_board = possible_board;
		}
		if (best_board.evaluation >= beta) {
			return true;
		}
		if (best_board.evaluation > alpha) {
			alpha = best_board.evaluation;
		}
	}
	else {
		if (possible_board.evaluation < best_board.evaluation) {
			best_board = possible_board;
		}
		if (best_board.evaluation <= alpha) {
			return true;
		}
		if (best_board.evaluation < beta) {
			beta = best_board.evaluation;
		}
	}
	return false;
}
