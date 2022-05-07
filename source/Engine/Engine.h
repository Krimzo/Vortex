#pragma once

#include "Board/Board.h"


namespace Engine {
	inline int calls = 0;
	inline kl::timer timer = {};
	inline const int MaxDepth = 6;

	float Evaluate(const Board& board);

	Info BestMove(const Board& board, bool whitesTurn, int depth, float alpha, float beta);
};
