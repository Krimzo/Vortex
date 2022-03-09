#pragma once

#include "Chess/Move.h"


class BoardState {
public:
	float eval;
	Move move;

	BoardState() {
		eval = 0.0f;
	}
	BoardState(float eval) {
		this->eval = eval;
	}
	BoardState(float eval, const Move& move) {
		this->eval = eval;
		this->move = move;
	}
};
