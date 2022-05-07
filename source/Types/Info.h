#pragma once

#include "Types/Move.h"


class Info {
public:
	float eval = 0.0f;
	Move bestMove;

	Info() {}
	Info(float eval) : eval(eval) {}
	Info(float eval, const Move& move) : eval(eval), bestMove(bestMove) {}
};
