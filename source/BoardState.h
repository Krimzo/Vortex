#pragma once

#include "Move.h"


class BoardState {
public:
	float eval = 0.0f;
	Move move;

	BoardState();
	BoardState(float eval);
	BoardState(float eval, const Move& move);
};
