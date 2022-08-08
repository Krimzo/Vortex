#pragma once

#include "Board/Board.h"


class Engine {
	kl::uint m_SearchDepth = 0;

	kl::uint64 m_CallCount = 0;
	float m_SearchTime = 0.0f;

	BoardInfo search(const Board& board, bool whitesTurn, kl::uint depth, float alpha, float beta, kl::Function<void(const Board&)> futureBoardCallback);

public:
	Engine() {}

	kl::uint getSearchDepth() const;
	kl::uint64 getCallCount() const;
	float getSearchTime() const;

	float evaluate(const Board& board);

	BoardInfo search(const Board& board, kl::uint searchDepth, bool searchDisplay = false);
};
