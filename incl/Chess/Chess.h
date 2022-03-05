#pragma once

#include "KrimzLib/KrimzLib.hpp"

#include "Chess/Piece.h"
#include "Chess/Board.h"


inline kl::window win;

void Update();
void Logic();

struct BestInfo {
	float eval;
	kl::int2 move;

	BestInfo() {
		eval = 0.0f;
		move = kl::int2(-1);
	}
	BestInfo(float eval, const kl::int2& move) {
		this->eval = eval;
		this->move = move;
	}
};
BestInfo BestMoveMT(const std::vector<Piece>& board);
