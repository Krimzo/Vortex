#pragma once

#include "board/moves.h"


namespace vtx {
	struct SearchResult
	{
		Board board;
		int depth = 0;
		float time = 0.0f;
	};
}

namespace vtx {
	struct Engine
	{
		Engine() = default;

		float evaluate(const Board& board) const;
		SearchResult search(Board& board, int max_depth);

	private:
		Board search_rec(Board& board, int max_depth, int depth, float alpha, float beta);
		bool piece_type_check(const Board& board, Piece piece);
		bool evaluation_check(bool white_to_play, float& alpha, float& beta, const Board& possible_board, Board& best_board);
	};
}
