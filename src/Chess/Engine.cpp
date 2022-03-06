#include "Chess/Engine.h"


float Engine::Evaluate(const Board& board) {
	float eval = 0.0f;
	bool whiteKingExists = false;
	bool blackKingExists = false;
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
			whiteKingExists = true;
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
			blackKingExists = true;
			break;
		}
	}

	// King check
	if (!blackKingExists) {
		return INFINITY;
	}
	if (!whiteKingExists) {
		return -INFINITY;
	}

	// Eval return
	return eval;
}

BestInfo Engine::BestMove(const Board& board) {
	// Game finished check
	const float currEval = Engine::Evaluate(board);
	if (currEval == -INFINITY || currEval == INFINITY) {
		return BestInfo(currEval);
	}

	// Min data buffer
	BestInfo minInfos[64];
	for (BestInfo& ref : minInfos) {
		ref = BestInfo(INFINITY);
	}

	// Threads
	std::thread threads[64];
	for (int i = 0; i < 64; i++) {
		threads[i] = std::thread([&](int t) {
			if (board.pieces[t].color() < 0) {
				const std::vector<Move> possibleMoves = board.getMoves(t);
				for (const Move& m : possibleMoves) {
					// Copy board and play the move
					Board futureBoard = board;
					futureBoard.playMove(m);

					// Find best move for future board
					const float futureEval = Engine::BestMoveRec(futureBoard, true, 1, -INFINITY, INFINITY).eval;
					if (futureEval < minInfos[t].eval) {
						minInfos[t].eval = futureEval;
						minInfos[t].move = m;
					}
				}
			}
		}, i);
	}
	for (std::thread& t : threads) {
		t.join();
	}

	// Finding the minimum eval
	BestInfo minInfo = minInfos[0];
	for (const BestInfo& ref : minInfos) {
		if (ref.eval < minInfo.eval) {
			minInfo = ref;
		}
	}
	return minInfo;
}

BestInfo Engine::BestMoveRec(const Board& board, bool whitesTurn, int depth, float alpha, float beta) {
	// Game finished check
	const float currEval = Engine::Evaluate(board);
	if (currEval == -INFINITY || currEval == INFINITY || depth >= Engine::MaxDepth) {
		return BestInfo(currEval);
	}

	// Turn select
	if (!whitesTurn) {
		BestInfo minInfo(INFINITY);
		for (int p = 0; p < 64; p++) {
			if (board.pieces[p].color() < 0) {
				const std::vector<Move> possibleMoves = board.getMoves(p);
				for (const Move& m : possibleMoves) {
					// First setup
					if (minInfo.move.from.index == -1) {
						minInfo.move = m;
					}

					// Copy board and play the move
					Board futureBoard = board;
					futureBoard.playMove(m);

					// Find best move for future board
					const float futureEval = BestMoveRec(futureBoard, true, depth + 1, alpha, beta).eval;
					if (futureEval < minInfo.eval) {
						minInfo.eval = futureEval;
						minInfo.move = m;
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
		BestInfo maxInfo(-INFINITY);
		for (int p = 0; p < 64; p++) {
			if (board.pieces[p].color() > 0) {
				const std::vector<Move> possibleMoves = board.getMoves(p);
				for (const Move& m : possibleMoves) {
					// First setup
					if (maxInfo.move.from.index == -1) {
						maxInfo.move = m;
					}

					// Copy board and play the move
					Board futureBoard = board;
					futureBoard.playMove(m);

					// Find best move for future board
					const float futureEval = BestMoveRec(futureBoard, false, depth + 1, alpha, beta).eval;
					if (futureEval > maxInfo.eval) {
						maxInfo.eval = futureEval;
						maxInfo.move = m;
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
