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

BoardInfo Engine::search(const Board& board, kl::uint searchDepth, bool searchDisplay) {
	m_SearchDepth = searchDepth;

	m_CallCount = 0;
	kl::Timer timer = {};

	BoardInfo info;
	if (searchDisplay) {
		kl::Window window = { { 800, 800 }, "Search Display" };
		kl::Image frameBuffer = { window.getSize() };

		window.setResizeable(false);

		info = search(board, false, 0, -INFINITY, INFINITY, [&](const Board& futureBoard) {
			futureBoard.drawToImage(frameBuffer);
			window.drawImage(frameBuffer);
			window.process(false);
		});
	}
	else {
		info = search(board, false, 0, -INFINITY, INFINITY, [](const Board&) {});
	}

	m_SearchTime = timer.getElapsed();

	return info;
}

BoardInfo Engine::search(const Board& board, bool whitesTurn, kl::uint depth, float alpha, float beta, kl::Function<void(const Board&)> futureBoardCallback) {
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
					Board futureBoard = board;
					futureBoard.playMove(move);

					futureBoardCallback(futureBoard);

					BoardInfo futureInfo = search(futureBoard, !whitesTurn, depth + 1, alpha, beta, futureBoardCallback);

					if (futureInfo.evaluation > maxState.evaluation) {
						maxState.evaluation = futureInfo.evaluation;
						maxState.bestMove = move;
					}

					alpha = max(alpha, futureInfo.evaluation);
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
					Board futureBoard = board;
					futureBoard.playMove(move);

					futureBoardCallback(futureBoard);

					BoardInfo futureInfo = search(futureBoard, !whitesTurn, depth + 1, alpha, beta, futureBoardCallback);

					if (futureInfo.evaluation < minState.evaluation) {
						minState.evaluation = futureInfo.evaluation;
						minState.bestMove = move;
					}

					beta = min(beta, futureInfo.evaluation);
					if (beta <= alpha) {
						return minState;
					}
				}
			}
		}

		return minState;
	}
}
