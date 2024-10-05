#include "engine/engine.h"


vtx::board vtx::engine::find_best_board_init(board& board, const uint8_t search_depth, const bool parallel)
{
	// Reset
	call_count_ = 0;
	search_depth_ = search_depth;
	vtx::board result = {};

	// Search
	const kl::timer timer = {};
	if (parallel) {
		result = find_best_board_parallel(board, 0, -INFINITY, INFINITY);
	}
	else {
		result = find_best_board(board, 0, -INFINITY, INFINITY);
	}
	search_time_ = timer.get_elapsed();

	// Finalize
	return result;
}

vtx::board vtx::engine::find_best_board(board& board, const int depth, float alpha, float beta)
{
	// Evaluation
	call_count_ += 1;
	static_evaluation(board);
	if (depth > search_depth_ || board.evaluation < -1e4f || board.evaluation > 1e4f) {
		return board;
	}

	// Setup
	vtx::board best_position = {};
	best_position.evaluation = (board.white_to_play ? -INFINITY : INFINITY);

	std::vector<vtx::board> possible_boards = {};
	possible_boards.reserve(50);
	
	// Search
	for (int i = 0; i < 64; i++) {
		const piece& piece = board[i];
		if (!piece_type_check(board, piece)) {
			continue;
		}

		possible_boards.clear();
		get_piece_moves(board, i, possible_boards);

		for (auto& possible_board : possible_boards) {
			possible_board.evaluation = find_best_board(possible_board, depth + 1, alpha, beta).evaluation;

			if (evaluation_check(board.white_to_play, alpha, beta, possible_board, best_position)) {
				return best_position;
			}
		}
	}
	return best_position;
}

vtx::board vtx::engine::find_best_board_parallel(board& board, const int depth, std::atomic<float> alpha, std::atomic<float> beta)
{
	// Evaluate
	call_count_ += 1;
	static_evaluation(board);
	if (depth > search_depth_ || board.evaluation < -1e4f || board.evaluation > 1e4f) {
		return board;
	}

	// Setup
	vtx::board best_position = {};
	best_position.evaluation = (board.white_to_play ? -INFINITY : INFINITY);

	std::vector<vtx::board> possible_boards = {};
	possible_boards.reserve(50);

	// Search
	for (int i = 0; i < 64; i++) {
		const piece& piece = board[i];
		if (!piece_type_check(board, piece)) {
			continue;
		}

		possible_boards.clear();
		get_piece_moves(board, i, possible_boards);

		for (auto& possible_board : possible_boards) {
			possible_board.evaluation = find_best_board_parallel(possible_board, depth + 1, alpha.load(), beta.load()).evaluation;

			if (evaluation_check_parallel(board.white_to_play, alpha, beta, possible_board, best_position)) {
				return best_position;
			}
		}
	}
	return best_position;
}

bool vtx::engine::piece_type_check(const board& board, const piece& piece)
{
	if (board.white_to_play && !piece.is_white()) {
		return false;
	}
	if (!board.white_to_play && !piece.is_black()) {
		return false;
	}
	return true;
}

bool vtx::engine::evaluation_check(const bool white_to_play, float& alpha, float& beta, const board& possible_board, board& best_board)
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

bool vtx::engine::evaluation_check_parallel(const bool white_to_play, std::atomic<float>& alpha, std::atomic<float>& beta, const board& possible_board, board& best_board)
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
