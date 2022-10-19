#pragma once

#include "Position/Position.h"


class Engine {
	int m_searchDepth = 0;
	kl::uint64 m_callCount = 0;

	kl::Timer m_timer = {};
	float m_searchTime = 0.0f;

	Position findBest(const Position& position, int depth, float alpha, float beta);

public:
	Engine() {}

	int getSearchDepth() const;
	kl::uint64 getCallCount() const;
	float getSearchTime() const;

	float evaluate(const Position& position);
	Position findBest(const Position& position, int searchDepth);
};
