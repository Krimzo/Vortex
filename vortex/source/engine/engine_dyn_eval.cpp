#include "vortex.h"


static constexpr int64_t WIN_THRESHOLD = 100'000;

static constexpr bool is_winning(int64_t value)
{
	return value > WIN_THRESHOLD || value < -WIN_THRESHOLD;
}

static constexpr bool is_limit(int64_t value)
{
    return value == MIN_EVAL || value == MAX_EVAL;
}

int64_t vtx::Engine::dyn_eval(Board const& board, int depth, int64_t alpha, int64_t beta, Board* out_best_board)
{
	++calls;
	if (int64_t eval = static_eval(board); (depth >= depth_limit * 2) || is_winning(eval))
		return eval;

	int64_t eval = board.white_to_play ? MIN_EVAL : MAX_EVAL;
	for (int i = 0; i < 64; i++) {
		if (!(board.white_to_play && board[i].is_white()) && !(!board.white_to_play && board[i].is_black()))
			continue;

		get_piece_moves(board, i, [&](Board& poss_board)
			{
				int64_t poss_eval = dyn_eval(poss_board, depth + 1, alpha, beta, nullptr);
				if (is_limit(eval) || (board.white_to_play && poss_eval > eval) || (!board.white_to_play && poss_eval < eval)) {
					eval = poss_eval;
					if (out_best_board)
						*out_best_board = poss_board;
				}

				if (board.white_to_play)
					alpha = kl::max(alpha, eval);
				else
					beta = kl::min(beta, eval);

				if (beta <= alpha) {
					i = 64;
					return true;
				}
				return false;
			});
	}
	return eval;
}
