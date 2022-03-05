#include "Chess/Chess.h"


float Evaluate(const std::vector<Piece>& board) {
	float eval = 0.0f;
	bool whiteKingExists = false;
	bool blackKingExists = false;
	for (Piece p : board) {
		switch (p) {
		case WPawn:
			eval += 1.0f;
			break;
		case WKnight:
			eval += 3.0f;
			break;
		case WBishop:
			eval += 3.0f;
			break;
		case WRook:
			eval += 5.0f;
			break;
		case WQueen:
			eval += 9.0f;
			break;
		case WKing:
			whiteKingExists = true;
			break;

		case BPawn:
			eval -= 1.0f;
			break;
		case BKnight:
			eval -= 3.0f;
			break;
		case BBishop:
			eval -= 3.0f;
			break;
		case BRook:
			eval -= 5.0f;
			break;
		case BQueen:
			eval -= 9.0f;
			break;
		case BKing:
			blackKingExists = true;
			break;
		}
	}
	if (!whiteKingExists) {
		return -INFINITY;
	}
	if (!blackKingExists) {
		return INFINITY;
	}
	return eval;
}

const int MAX_DEPTH = 5;

BestInfo BestMove(const std::vector<Piece>& board, bool whitesTurn, int depth, float alpha, float beta) {
	// Game finished check
	const float currEval = Evaluate(board);
	if (currEval == -INFINITY || currEval == INFINITY || depth >= MAX_DEPTH) {
		return BestInfo(currEval, kl::int2(-1));
	}

	// Turn select
	if (!whitesTurn) {
		BestInfo minInfo(INFINITY, kl::int2(-1));
		for (int p = 0; p < 64; p++) {
			if (PieceColor(board[p]) < 0) {
				const std::vector<int> possibleMoves = PieceMoves(board, p);
				for (int m : possibleMoves) {
					// First setup
					if (minInfo.move.x == -1) {
						minInfo.move.x = p;
						minInfo.move.y = m;
					}

					// Copy board and play the move
					std::vector<Piece> futureBoard = board;
					futureBoard[m] = futureBoard[p];
					futureBoard[p] = Piece::None;

					// Find best move for future board
					const float futureEval = BestMove(futureBoard, true, depth + 1, alpha, beta).eval;
					if (futureEval < minInfo.eval) {
						minInfo.eval = futureEval;
						minInfo.move.x = p;
						minInfo.move.y = m;
					}

					// Alpha beat pruning
					beta = min(beta, futureEval);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}
		return minInfo;
	}
	else {
		BestInfo maxInfo(-INFINITY, kl::int2(-1));
		for (int p = 0; p < 64; p++) {
			if (PieceColor(board[p]) > 0) {
				const std::vector<int> possibleMoves = PieceMoves(board, p);
				for (int m : possibleMoves) {
					// First setup
					if (maxInfo.move.x == -1) {
						maxInfo.move.x = p;
						maxInfo.move.y = m;
					}

					// Copy board and play the move
					std::vector<Piece> futureBoard = board;
					futureBoard[m] = futureBoard[p];
					futureBoard[p] = Piece::None;

					// Find best move for future board
					const float futureEval = BestMove(futureBoard, false, depth + 1, alpha, beta).eval;
					if (futureEval > maxInfo.eval) {
						maxInfo.eval = futureEval;
						maxInfo.move.x = p;
						maxInfo.move.y = m;
					}

					// Alpha beta pruning
					alpha = max(alpha, futureEval);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}
		return maxInfo;
	}
}
BestInfo BestMoveMT(const std::vector<Piece>& board) {
	// Game finished check
	const float currEval = Evaluate(board);
	if (currEval == -INFINITY || currEval == INFINITY) {
		return BestInfo(currEval, kl::int2(-1));
	}

	// Min data buffer
	BestInfo minInfos[4] = {
		BestInfo(INFINITY, kl::int2(-1)),
		BestInfo(INFINITY, kl::int2(-1)),
		BestInfo(INFINITY, kl::int2(-1)),
		BestInfo(INFINITY, kl::int2(-1))
	};

	// Parallel board loop
	kl::thread::parallelFor(0, 64, [&](int t, int p) {
		// Recomputing index
		p = (p / 16) + (p % 16) * 4;

		// Checking piece color
		if (PieceColor(board[p]) < 0) {
			const std::vector<int> possibleMoves = PieceMoves(board, p);
			for (int m : possibleMoves) {
				// First setup
				if (minInfos[t].move.x == -1) {
					minInfos[t].move.x = p;
					minInfos[t].move.y = m;
				}

				// Copy board and play the move
				std::vector<Piece> futureBoard = board;
				futureBoard[m] = futureBoard[p];
				futureBoard[p] = Piece::None;

				// Find best move for future board
				const float futureEval = BestMove(futureBoard, true, 1, -INFINITY, INFINITY).eval;
				if (futureEval < minInfos[t].eval) {
					minInfos[t].eval = futureEval;
					minInfos[t].move.x = p;
					minInfos[t].move.y = m;
				}
			}
		}
	});

	// Finding the minimum eval
	BestInfo* minInfo = &minInfos[0];
	for (int i = 1; i < 4; i++) {
		if (minInfos[i].eval < minInfo->eval) {
			minInfo = &minInfos[i];
		}
	}
	return *minInfo;
}
