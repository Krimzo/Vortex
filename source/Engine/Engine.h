#pragma once

#include "Board/Board.h"


namespace Engine {
	inline size_t calls = 0;
	inline kl::timer timer = {};
	inline int SearchDepth = 5;

	float Evaluate(const Board& board);

	Info BestMove(const Board& board, bool whitesTurn, int depth, float alpha, float beta);
};
