#pragma once

#include "Board.h"


class Engine {
public:
	static const int MaxDepth;
	static int calls;
	static kl::timer timer;

	// Evaluates the position
	static float Evaluate(const Board& board);

	// Returns the best move
	static BoardState BestMove(const Board& board, bool whitesTurn, int depth, float alpha, float beta);
};
