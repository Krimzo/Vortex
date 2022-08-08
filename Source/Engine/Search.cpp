#include "Engine/Engine.h"


kl::uint Engine::getSearchDepth() const {
	return m_SearchDepth;
}

kl::uint64 Engine::getCallCount() const {
	return m_CallCount;
}

float Engine::getSearchTime() const {
	return m_SearchTime;
}

BoardInfo Engine::search(const Board& board, kl::uint searchDepth) {
	m_SearchDepth = searchDepth;

	m_CallCount = 0;
	kl::Timer timer = {};

	BoardInfo info = search(board, false, 0, -INFINITY, INFINITY);

	m_SearchTime = timer.getElapsed();

	return info;
}

BoardInfo Engine::search(const Board& board, bool whitesTurn, kl::uint depth, float alpha, float beta) {
	m_CallCount += 1;

	if (depth >= m_SearchDepth) {
		return { evaluate(board) };
	}

	if (whitesTurn) {
		BoardInfo maxState = { -INFINITY };

		for (int i = 0; i < 64; i++) {
			if (Board::IsWhite(board.getPiece(i))) {
				kl::Vector<Move> allMoves;
				board.getSquareMoves(i, allMoves);

				for (auto& move : allMoves) {
					if (board.getPiece(move.to.index) == Piece::BKing) {
						maxState.evaluation = INFINITY;
						maxState.bestMove = move;
						return maxState;
					}

					Board futureBoard = board;
					futureBoard.playMove(move);

					const float futureEval = search(futureBoard, !whitesTurn, depth + 1, alpha, beta).evaluation;

					if (futureEval > maxState.evaluation) {
						maxState.evaluation = futureEval;
						maxState.bestMove = move;
					}

					alpha = max(alpha, futureEval);
					if (beta <= alpha) {
						return maxState;
					}
				}
			}
		}
		return maxState;
	}
	else {
		BoardInfo minState = { INFINITY };

		for (int i = 0; i < 64; i++) {
			if (Board::IsBlack(board.getPiece(i))) {
				std::vector<Move> allMoves;
				board.getSquareMoves(i, allMoves);

				for (auto& move : allMoves) {
					if (board.getPiece(move.to.index) == Piece::WKing) {
						minState.evaluation = -INFINITY;
						minState.bestMove = move;
						return minState;
					}

					Board futureBoard = board;
					futureBoard.playMove(move);

					const float futureEval = search(futureBoard, !whitesTurn, depth + 1, alpha, beta).evaluation;

					if (futureEval < minState.evaluation) {
						minState.evaluation = futureEval;
						minState.bestMove = move;
					}

					beta = min(beta, futureEval);
					if (beta <= alpha) {
						return minState;
					}
				}
			}
		}
		return minState;
	}
}
