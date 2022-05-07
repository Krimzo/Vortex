#include "Engine/Engine.h"


float Engine::Evaluate(const Board& board) {
	float eval = 0.0f;
	for (auto& p : board.pieces) {
		eval += float(p);
	}
	return eval;
}

Info Engine::BestMove(const Board& board, bool whitesTurn, int depth, float alpha, float beta) {
	// Info
	Engine::calls++;

	// Depth and time check
	if (depth > MaxDepth) {
		return Info(Engine::Evaluate(board));
	}

	// Whos move
	if (whitesTurn) {
		Info maxState(-INFINITY);
		for (int i = 0; i < 64; i++) {
			if (Board::isWhite(board.pieces[i])) {
				std::vector<Move> allMoves;
				board.getMoves(i, allMoves);
				for (auto& move : allMoves) {
					// Checkmate check
					if (board.pieces[move.to.index] == Piece::BKing) {
						maxState.eval = INFINITY;
						maxState.bestMove = move;
						return maxState;
					}

					// Future board
					Board futureBoard = board;
					futureBoard.playMove(move);

					// Future board eval
					const float futureEval = BestMove(futureBoard, !whitesTurn, depth + 1, alpha, beta).eval;

					// Max eval save
					if (futureEval > maxState.eval) {
						maxState.eval = futureEval;
						maxState.bestMove = move;
					}

					// Alpha beta pruning
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
		Info minState(INFINITY);
		for (int i = 0; i < 64; i++) {
			if (Board::isBlack(board.pieces[i])) {
				std::vector<Move> allMoves;
				board.getMoves(i, allMoves);
				for (auto& move : allMoves) {
					// Checkmate check
					if (board.pieces[move.to.index] == Piece::WKing) {
						minState.eval = -INFINITY;
						minState.bestMove = move;
						return minState;
					}

					// Future board
					Board futureBoard = board;
					futureBoard.playMove(move);

					// Future board eval
					const float futureEval = BestMove(futureBoard, !whitesTurn, depth + 1, alpha, beta).eval;

					// Min eval save
					if (futureEval < minState.eval) {
						minState.eval = futureEval;
						minState.bestMove = move;
					}

					// Alpha beta pruning
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
