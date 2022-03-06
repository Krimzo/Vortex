#pragma once

#include "Chess/Move.h"


class BestInfo {
public:
	float eval;
	Move move;

	BestInfo() {
		eval = 0.0f;
	}
	BestInfo(float eval) {
		this->eval = eval;
	}
	BestInfo(float eval, const Move& move) {
		this->eval = eval;
		this->move = move;
	}
};
