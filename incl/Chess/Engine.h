#pragma once

#include "Chess/Board.h"


class Engine {
public:
	// Search limits
	static const int MaxDepth;

	// Info
	static int calls;
	static kl::timer timer;

public:
	// Evaluates the position
	static float Evaluate(const Board& board);

	// Returns the best move
	static BoardState BestMove(const Board& board, bool whitesTurn, int depth, float alpha, float beta);
};
