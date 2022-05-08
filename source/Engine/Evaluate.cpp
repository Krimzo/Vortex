#include "Engine/Engine.h"


// Value tables
// Pawns
static const float wPawnValueTable[64] = {
	 0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
	 0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f,
	 0.10f,  0.10f,  0.20f,  0.30f,  0.30f,  0.20f,  0.10f,  0.10f,
	 0.05f,  0.05f,  0.10f,  0.25f,  0.25f,  0.10f,  0.05f,  0.05f,
	 0.00f,  0.00f,  0.00f,  0.20f,  0.20f,  0.00f,  0.00f,  0.00f,
	 0.05f, -0.05f, -0.10f,  0.00f,  0.00f, -0.10f, -0.05f,  0.05f,
	 0.05f,  0.10f,  0.10f, -0.20f, -0.20f,  0.10f,  0.10f,  0.05f,
	 0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
};
static const float bPawnValueTable[64] = {
	 0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
	 0.05f,  0.10f,  0.10f, -0.20f, -0.20f,  0.10f,  0.10f,  0.05f,
	 0.05f, -0.05f, -0.10f,  0.00f,  0.00f, -0.10f, -0.05f,  0.05f,
	 0.00f,  0.00f,  0.00f,  0.20f,  0.20f,  0.00f,  0.00f,  0.00f,
	 0.05f,  0.05f,  0.10f,  0.25f,  0.25f,  0.10f,  0.05f,  0.05f,
	 0.10f,  0.10f,  0.20f,  0.30f,  0.30f,  0.20f,  0.10f,  0.10f,
	 0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f,
	 0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
};

// Knights
static const float wKnightValueTable[64] = {
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
	-0.40f, -0.20f,  0.00f,  0.00f,  0.00f,  0.00f, -0.20f, -0.40f,
	-0.30f,  0.00f,  0.10f,  0.15f,  0.15f,  0.10f,  0.00f, -0.30f,
	-0.30f,  0.05f,  0.15f,  0.20f,  0.20f,  0.15f,  0.05f, -0.30f,
	-0.30f,  0.00f,  0.15f,  0.20f,  0.20f,  0.15f,  0.00f, -0.30f,
	-0.30f,  0.05f,  0.10f,  0.15f,  0.15f,  0.10f,  0.05f, -0.30f,
	-0.40f, -0.20f,  0.00f,  0.05f,  0.05f,  0.00f, -0.20f, -0.40f,
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
};
static const float bKnightValueTable[64] = {
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
	-0.40f, -0.20f,  0.00f,  0.05f,  0.05f,  0.00f, -0.20f, -0.40f,
	-0.30f,  0.05f,  0.10f,  0.15f,  0.15f,  0.10f,  0.05f, -0.30f,
	-0.30f,  0.00f,  0.15f,  0.20f,  0.20f,  0.15f,  0.00f, -0.30f,
	-0.30f,  0.05f,  0.15f,  0.20f,  0.20f,  0.15f,  0.05f, -0.30f,
	-0.30f,  0.00f,  0.10f,  0.15f,  0.15f,  0.10f,  0.00f, -0.30f,
	-0.40f, -0.20f,  0.00f,  0.00f,  0.00f,  0.00f, -0.20f, -0.40f,
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
};

// Bishops
static const float wBishopValueTable[64] = {
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
	-0.10f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.05f,  0.10f,  0.10f,  0.05f,  0.00f, -0.10f,
	-0.10f,  0.05f,  0.05f,  0.10f,  0.10f,  0.05f,  0.05f, -0.10f,
	-0.10f,  0.00f,  0.10f,  0.10f,  0.10f,  0.10f,  0.00f, -0.10f,
	-0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f, -0.10f,
	-0.10f,  0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.05f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
};
static const float bBishopValueTable[64] = {
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
	-0.10f,  0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.05f, -0.10f,
	-0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f, -0.10f,
	-0.10f,  0.00f,  0.10f,  0.10f,  0.10f,  0.10f,  0.00f, -0.10f,
	-0.10f,  0.05f,  0.05f,  0.10f,  0.10f,  0.05f,  0.05f, -0.10f,
	-0.10f,  0.00f,  0.05f,  0.10f,  0.10f,  0.05f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
};

// Rooks
static const float wRookValueTable[64] = {
	 0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
	 0.05f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	 0.00f,  0.00f,  0.00f,  0.05f,  0.05f,  0.00f,  0.00f,  0.00f,
};
static const float bRookValueTable[64] = {
	 0.00f,  0.00f,  0.00f,  0.05f,  0.05f,  0.00f,  0.00f,  0.00f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f,
	 0.05f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.05f,
	 0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,
};

// Queens											
static const float wQueenValueTable[64] = {
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
	-0.10f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.10f,
	-0.05f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.05f,
	 0.00f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.05f,
	-0.10f,  0.05f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.05f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
};
static const float bQueenValueTable[64] = {
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
	-0.10f,  0.00f,  0.05f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.10f,  0.05f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.10f,
	 0.00f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.05f,
	-0.10f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
};

// Kings											
static const float wKingMidValueTable[64] = {
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.20f, -0.30f, -0.30f, -0.40f, -0.40f, -0.30f, -0.30f, -0.20f,
	-0.10f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.10f,
	 0.20f,  0.20f,  0.00f,  0.00f,  0.00f,  0.00f,  0.20f,  0.20f,
	 0.20f,  0.30f,  0.10f,  0.00f,  0.00f,  0.10f,  0.30f,  0.20f,
};
static const float bKingMidValueTable[64] = {
	 0.20f,  0.30f,  0.10f,  0.00f,  0.00f,  0.10f,  0.30f,  0.20f,
	 0.20f,  0.20f,  0.00f,  0.00f,  0.00f,  0.00f,  0.20f,  0.20f,
	-0.10f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.10f,
	-0.20f, -0.30f, -0.30f, -0.40f, -0.40f, -0.30f, -0.30f, -0.20f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
};
static const float wKingEndValueTable[64] = {
	-0.50f, -0.40f, -0.30f, -0.20f, -0.20f, -0.30f, -0.40f, -0.50f,
	-0.30f, -0.20f, -0.10f,  0.00f,  0.00f, -0.10f, -0.20f, -0.30f,
	-0.30f, -0.10f,  0.20f,  0.30f,  0.30f,  0.20f, -0.10f, -0.30f,
	-0.30f, -0.10f,  0.30f,  0.40f,  0.40f,  0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f,  0.30f,  0.40f,  0.40f,  0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f,  0.20f,  0.30f,  0.30f,  0.20f, -0.10f, -0.30f,
	-0.30f, -0.30f,  0.00f,  0.00f,  0.00f,  0.00f, -0.30f, -0.30f,
	-0.50f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.50f,
};
static const float bKingEndValueTable[64] = {
	-0.50f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.50f,
	-0.30f, -0.30f,  0.00f,  0.00f,  0.00f,  0.00f, -0.30f, -0.30f,
	-0.30f, -0.10f,  0.20f,  0.30f,  0.30f,  0.20f, -0.10f, -0.30f,
	-0.30f, -0.10f,  0.30f,  0.40f,  0.40f,  0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f,  0.30f,  0.40f,  0.40f,  0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f,  0.20f,  0.30f,  0.30f,  0.20f, -0.10f, -0.30f,
	-0.30f, -0.20f, -0.10f,  0.00f,  0.00f, -0.10f, -0.20f, -0.30f,
	-0.50f, -0.40f, -0.30f, -0.20f, -0.20f, -0.30f, -0.40f, -0.50f,
};


bool wInEndgame(const Board& board) {
	int minorPieces = 0;
	for (auto& p : board.pieces) {
		switch (p) {
		case Piece::BQueen:
			return false;

		case Piece::BKnight:
		case Piece::BBishop:
		case Piece::BRook:
			if (++minorPieces > 2) {
				return false;
			}
		}
	}
	return true;
}
bool bInEndgame(const Board& board) {
	int minorPieces = 0;
	for (auto& p : board.pieces) {
		switch (p) {
		case Piece::WQueen:
			return false;

		case Piece::WKnight:
		case Piece::WBishop:
		case Piece::WRook:
			if (++minorPieces > 2) {
				return false;
			}
		}
	}
	return true;
}


float Engine::Evaluate(const Board& board) {
	float eval = 0.0f;
	for (int i = 0; i < 64; i++) {
		switch (board.pieces[i]) {
		case Piece::WPawn:
			eval += 1.0f;
			eval += wPawnValueTable[i];
			break;
		case Piece::WKnight:
			eval += 3.2f;
			eval += wKnightValueTable[i];
			break;
		case Piece::WBishop:
			eval += 3.3f;
			eval += wBishopValueTable[i];
			break;
		case Piece::WRook:
			eval += 5.0f;
			eval += wRookValueTable[i];
			break;
		case Piece::WQueen:
			eval += 9.0f;
			eval += wQueenValueTable[i];
			break;
		case Piece::WKing:
			eval += 1'000'000.0f;
			eval += wInEndgame(board) ? wKingEndValueTable[i] : wKingMidValueTable[i];
			break;

		case Piece::BPawn:
			eval -= 1.0f;
			eval -= bPawnValueTable[i];
			break;
		case Piece::BKnight:
			eval -= 3.2f;
			eval -= bKnightValueTable[i];
			break;
		case Piece::BBishop:
			eval -= 3.3f;
			eval -= bBishopValueTable[i];
			break;
		case Piece::BRook:
			eval -= 5.0f;
			eval -= bRookValueTable[i];
			break;
		case Piece::BQueen:
			eval -= 9.0f;
			eval -= bQueenValueTable[i];
			break;
		case Piece::BKing:
			eval -= 1'000'000.0f;
			eval -= bInEndgame(board) ? bKingEndValueTable[i] : bKingMidValueTable[i];
			break;
		}
	}
	return eval;
}
