#include "engine/engine.h"


vtx::board vtx::engine::find_best_position(const board& board, const int search_depth)
{
	call_count_ = 0;
	search_depth_ = search_depth;

	const kl::timer timer = {};
	const auto result = find_best_position(board, 0, -INFINITY, INFINITY);
	search_time_ = timer.get_elapsed();

	return result;
}

vtx::board vtx::engine::find_best_position(const board& board, const int depth, float alpha, float beta)
{
	call_count_ += 1;

	const float evaluation = static_evaluation(board);
	if (depth > search_depth_ || evaluation < -1e4f || evaluation > 1e4f) {
		vtx::board result = board;
		result.evaluation = evaluation;
		return result;
	}
	
	if (board.white_to_play) {
		vtx::board best_position = {};
		best_position.evaluation = -INFINITY;

		for (int i = 0; i < 64; i++) {
			if (const piece& piece = board[i]; piece.is_white()) {
				std::vector<vtx::board> possible_boards = {};
				get_piece_moves(board, i, possible_boards);

				for (auto& possible_board : possible_boards) {
					possible_board.evaluation = find_best_position(possible_board, depth + 1, alpha, beta).evaluation;

					if (possible_board.evaluation > best_position.evaluation) {
						best_position = possible_board;
					}

					if (best_position.evaluation >= beta) {
						return best_position;
					}

					alpha = max(alpha, best_position.evaluation);
				}
			}
		}

		return best_position;
	}
	else {
		vtx::board best_position = {};
		best_position.evaluation = INFINITY;
		
		for (int i = 0; i < 64; i++) {
			if (const piece& piece = board[i]; piece.is_black()) {
				std::vector<vtx::board> possible_boards = {};
				get_piece_moves(board, i, possible_boards);

				for (auto& possible_board : possible_boards) {
					possible_board.evaluation = find_best_position(possible_board, depth + 1, alpha, beta).evaluation;

					if (possible_board.evaluation < best_position.evaluation) {
						best_position = possible_board;
					}

					if (best_position.evaluation <= alpha) {
						return best_position;
					}
			
					beta = min(beta, best_position.evaluation);
				}
			}
		}

		return best_position;
	}
}
