#include "Engine/Engine.h"


int Engine::getSearchDepth() const {
	return m_searchDepth;
}

kl::uint64 Engine::getCallCount() const {
	return m_callCount;
}

float Engine::getSearchTime() const {
	return m_searchTime;
}

Position Engine::findBest(const Position& position, int searchDepth) {
	m_searchDepth = searchDepth;
	m_callCount = 0;

	m_timer.reset();
	Position result = findBest(position, 0, -INFINITY, INFINITY);
	m_searchTime = m_timer.getElapsed();

	return result;
}

Position Engine::findBest(const Position& position, int depth, float alpha, float beta) {
	m_callCount += 1;

	const float evaluation = evaluate(position);

	if (depth > m_searchDepth || evaluation < -1e4f || evaluation > 1e4f) {
		Position result = position;
		result.evaluation = evaluation;
		return result;
	}

	if (position.whiteToPlay) {
		Position bestPosition = {};
		bestPosition.evaluation = -INFINITY;

		for (int i = 0; i < 64; i++) {
			if (position.pieces[i].isWhite()) {
				kl::Vector<Position> allPositions = {};
				position.pieces[i].getMoves(position, i, allPositions);

				for (auto& position : allPositions) {
					const float futureEval = findBest(position, depth + 1, alpha, beta).evaluation;

					if (futureEval > bestPosition.evaluation) {
						bestPosition = position;
						bestPosition.evaluation = futureEval;
					}

					if (bestPosition.evaluation >= beta) {
						return bestPosition;
					}
					alpha = max(alpha, bestPosition.evaluation);
				}
			}
		}

		return bestPosition;
	}
	else {
		Position bestPosition = {};
		bestPosition.evaluation = INFINITY;

		for (int i = 0; i < 64; i++) {
			if (position.pieces[i].isBlack()) {
				kl::Vector<Position> allPositions = {};
				position.pieces[i].getMoves(position, i, allPositions);

				for (auto& position : allPositions) {
					const float futureEval = findBest(position, depth + 1, alpha, beta).evaluation;

					if (futureEval < bestPosition.evaluation) {
						bestPosition = position;
						bestPosition.evaluation = futureEval;
					}

					if (bestPosition.evaluation <= alpha) {
						return bestPosition;
					}
					beta = min(beta, bestPosition.evaluation);
				}
			}
		}

		return bestPosition;
	}
}
