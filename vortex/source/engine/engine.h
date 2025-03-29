#pragma once

#include "board/moves.h"


namespace vtx {
	struct SearchResult
	{
		Board board;
		int depth = 0;
		uint64_t calls = 0;
		int64_t eval = 0;
		float time = 0.0f;
	};
}

namespace vtx {
	struct Engine
	{
		int depth_limit = 3;
		uint64_t calls = 0;

		SearchResult search(Board const& board);

		int64_t static_eval(Board const& board);
		int64_t dyn_eval(Board const& board, int depth, int64_t alpha, int64_t beta, Board* out_best_board);
	};
}
