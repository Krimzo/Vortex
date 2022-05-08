#pragma once

#include "Board/Board.h"


namespace Engine {
	inline size_t calls = 0;
	inline kl::timer timer = {};
	inline uint32_t SearchDepth = 5;

	float Evaluate(const Board& board);

	Info Search(const Board& board, bool whitesTurn, uint32_t depth, float alpha, float beta);
};
