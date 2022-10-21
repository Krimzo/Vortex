#include "engine/engine.h"


engine::engine()
{}

int engine::get_search_depth() const
{
	return search_depth_;
}

uint64_t engine::get_call_count() const
{
	return call_count_;
}

float engine::get_search_time() const
{
	return search_time_;
}

position engine::find_best_position(const position& position, const int search_depth)
{
	call_count_ = 0;
	search_depth_ = search_depth;

	const kl::timer timer = {};
	const ::position result = find_best_position(position, 0, -INFINITY, INFINITY);
	search_time_ = timer.get_elapsed();

	return result;
}

position engine::find_best_position(const position& position, const int depth, float alpha, float beta)
{
	call_count_ += 1;

	if (const float evaluation = static_evaluation(position); depth > search_depth_ || evaluation < -1e4f || evaluation > 1e4f) {
		::position result = position;
		result.evaluation = evaluation;
		return result;
	}
	
	if (position.white_to_play) {
		::position best_position = {};
		best_position.evaluation = -INFINITY;

		for (int i = 0; i < 64; i++) {
			if (const piece& piece = position.pieces[i]; piece.is_white()) {
				std::vector<::position> possible_positions = {};
				piece.get_moves(position, i, possible_positions);

				for (auto& possible_position : possible_positions) {
					possible_position.evaluation = find_best_position(possible_position, depth + 1, alpha, beta).evaluation;

					if (possible_position.evaluation > best_position.evaluation) {
						best_position = possible_position;
					}

					if (best_position.evaluation >= beta) {
						return best_position;
					}

					alpha = std::max(alpha, best_position.evaluation);
				}
			}
		}

		return best_position;
	}
	else {
		::position best_position = {};
		best_position.evaluation = INFINITY;
		
		for (int i = 0; i < 64; i++) {
			if (const piece& piece = position.pieces[i]; piece.is_black()) {
				std::vector<::position> piece_possible_positions = {};
				piece.get_moves(position, i, piece_possible_positions);

				for (auto& possible_position : piece_possible_positions) {
					possible_position.evaluation = find_best_position(possible_position, depth + 1, alpha, beta).evaluation;

					if (possible_position.evaluation < best_position.evaluation) {
						best_position = possible_position;
					}

					if (best_position.evaluation <= alpha) {
						return best_position;
					}
			
					beta = std::min(beta, best_position.evaluation);
				}
			}
		}

		return best_position;
	}
}
