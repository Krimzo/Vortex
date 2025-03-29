#include "vortex.h"


vtx::SearchResult vtx::Engine::search(Board const& board)
{
	calls = 0;
	uint64_t start_time = kl::time::now();
	SearchResult result;
	result.board = board;
	result.depth = depth_limit;
	result.eval = dyn_eval(board, 0,
		std::numeric_limits<int64_t>::min(),
		std::numeric_limits<int64_t>::max(),
		&result.board);
	result.calls = calls;
	result.time = kl::time::elapsed(start_time, kl::time::now());
	return result;
}
