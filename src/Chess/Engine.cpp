#include "Chess/Engine.h"


// Search limits
const int Engine::MaxDepth = 6;

// Info
int Engine::calls = 0;
kl::timer Engine::timer = kl::timer();

float Engine::Evaluate(const Board& board) {
	float eval = 0.0f;
	for (Piece p : board.pieces) {
		switch (p.type) {
		case Piece::Type::WPawn:
			eval += 1.0f;
			break;
		case Piece::Type::WKnight:
			eval += 3.0f;
			break;
		case Piece::Type::WBishop:
			eval += 3.0f;
			break;
		case Piece::Type::WRook:
			eval += 5.0f;
			break;
		case Piece::Type::WQueen:
			eval += 9.0f;
			break;
		case Piece::Type::WKing:
			eval += 1000.0f;
			break;

		case Piece::Type::BPawn:
			eval -= 1.0f;
			break;
		case Piece::Type::BKnight:
			eval -= 3.0f;
			break;
		case Piece::Type::BBishop:
			eval -= 3.0f;
			break;
		case Piece::Type::BRook:
			eval -= 5.0f;
			break;
		case Piece::Type::BQueen:
			eval -= 9.0f;
			break;
		case Piece::Type::BKing:
			eval -= 1000.0f;
			break;
		}
	}
	return eval;
}

BestInfo Engine::BestMove(const Board& board, bool whitesTurn, int depth, float alpha, float beta) {
	// Info
	Engine::calls++;

	// Game finished check
	const float currEval = Engine::Evaluate(board);
	if (currEval < -500.0f || currEval > 500.0f || depth >= Engine::MaxDepth) {
		return BestInfo(currEval);
	}

	// Turn select
	if (!whitesTurn) {
		// Min Buffer
		BestInfo minInfo(INFINITY);

		// Piece loop
		for (int p = 0; p < 64; p++) {
			// Color check
			if (board.pieces[p].color() < 0) {
				// Move buffer
				const std::vector<Move> possibleMoves = board.getMoves(p);

				// Move loop
				for (const Move& m : possibleMoves) {
					// Copy board and play the move
					Board futureBoard = board;
					futureBoard.playMove(m);

					// Find best move for future board
					const float futureEval = BestMove(futureBoard, true, depth + 1, alpha, beta).eval;
					if (futureEval < minInfo.eval) {
						minInfo.eval = futureEval;
						minInfo.move = m;
					}

					// Alpha beat pruning
					beta = min(beta, futureEval);
					if (beta <= alpha) {
						return minInfo;
					}
				}
			}
		}
		return minInfo;
	}
	else {
		// Max buffer
		BestInfo maxInfo(-INFINITY);

		// Piece loop
		for (int p = 0; p < 64; p++) {
			// Color check
			if (board.pieces[p].color() > 0) {
				// Move buffer
				const std::vector<Move> possibleMoves = board.getMoves(p);

				// Move loop
				for (const Move& m : possibleMoves) {
					// Copy board and play the move
					Board futureBoard = board;
					futureBoard.playMove(m);

					// Find best move for future board
					const float futureEval = BestMove(futureBoard, false, depth + 1, alpha, beta).eval;
					if (futureEval > maxInfo.eval) {
						maxInfo.eval = futureEval;
						maxInfo.move = m;
					}

					// Alpha beta pruning
					alpha = max(alpha, futureEval);
					if (beta <= alpha) {
						return maxInfo;
					}
				}
			}
		}
		return maxInfo;
	}
}
