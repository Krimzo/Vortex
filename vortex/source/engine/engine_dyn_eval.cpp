#include "vortex.h"


float vtx::Engine::dyn_eval(Board const& board, int depth, float alpha, float beta, Board* out_best_board)
{
	++calls;

	if (float eval = static_eval(board); (depth >= depth_limit * 2) || eval < -1000.0f || eval > 1000.0f)
		return eval;

	float eval = board.white_to_play ? -INF : INF;
	for (int i = 0; i < 64; i++) {
		if (!(board.white_to_play && board[i].is_white()) && !(!board.white_to_play && board[i].is_black()))
			continue;

		get_piece_moves(board, i, [&](Board& poss_board)
			{
				float poss_eval = dyn_eval(poss_board, depth + 1, alpha, beta, nullptr);
				if (isinf(eval) || (board.white_to_play && poss_eval > eval) || (!board.white_to_play && poss_eval < eval)) {
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
