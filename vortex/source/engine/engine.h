#pragma once

#include "board/moves.h"


inline constexpr auto INF = std::numeric_limits<float>::infinity();

namespace vtx {
	struct SearchResult
	{
		Board board;
		int depth = 0;
		uint64_t calls = 0;
		float eval = 0.0f;
		float time = 0.0f;
	};
}

namespace vtx {
	struct Engine
	{
		int depth_limit = 2;
		uint64_t calls = 0;

		SearchResult search(Board const& board);

		float static_eval(Board const& board);
		float dyn_eval(Board const& board, int depth, float alpha, float beta, Board* out_best_board);
	};
}
