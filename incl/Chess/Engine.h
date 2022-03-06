#pragma once

#include "Chess/Board.h"


class Engine {
public:
	// Max search depth
	static const int MaxDepth = 6;

public:
	// Evaluates the position
	static float Evaluate(const Board& board);

	// Returns the best move
	static BestInfo BestMove(const Board& board);
	static BestInfo BestMoveRec(const Board& board, bool whitesTurn, int depth, float alpha, float beta);
};
