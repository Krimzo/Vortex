#include "Engine/Engine.h"


// Value tables
// Pawns
static const float WhitePawnValueTable[64] = {
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
	0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
	0.10f, 0.10f, 0.20f, 0.30f, 0.30f, 0.20f, 0.10f, 0.10f,
	0.05f, 0.05f, 0.10f, 0.25f, 0.25f, 0.10f, 0.05f, 0.05f,
	0.00f, 0.00f, 0.00f, 0.20f, 0.20f, 0.00f, 0.00f, 0.00f,
	0.05f, -0.05f, -0.10f, 0.00f, 0.00f, -0.10f, -0.05f, 0.05f,
	0.05f, 0.10f, 0.10f, -0.20f, -0.20f, 0.10f, 0.10f, 0.05f,
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
};
static const float BlackPawnValueTable[64] = {
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
	0.05f, 0.10f, 0.10f, -0.20f, -0.20f, 0.10f, 0.10f, 0.05f,
	0.05f, -0.05f, -0.10f, 0.00f, 0.00f, -0.10f, -0.05f, 0.05f,
	0.00f, 0.00f, 0.00f, 0.20f, 0.20f, 0.00f, 0.00f, 0.00f,
	0.05f, 0.05f, 0.10f, 0.25f, 0.25f, 0.10f, 0.05f, 0.05f,
	0.10f, 0.10f, 0.20f, 0.30f, 0.30f, 0.20f, 0.10f, 0.10f,
	0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
};

// Knights
static const float WhiteKnightValueTable[64] = {
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
	-0.40f, -0.20f, 0.00f, 0.00f, 0.00f, 0.00f, -0.20f, -0.40f,
	-0.30f, 0.00f, 0.10f, 0.15f, 0.15f, 0.10f, 0.00f, -0.30f,
	-0.30f, 0.05f, 0.15f, 0.20f, 0.20f, 0.15f, 0.05f, -0.30f,
	-0.30f, 0.00f, 0.15f, 0.20f, 0.20f, 0.15f, 0.00f, -0.30f,
	-0.30f, 0.05f, 0.10f, 0.15f, 0.15f, 0.10f, 0.05f, -0.30f,
	-0.40f, -0.20f, 0.00f, 0.05f, 0.05f, 0.00f, -0.20f, -0.40f,
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
};
static const float BlackKnightValueTable[64] = {
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
	-0.40f, -0.20f, 0.00f, 0.05f, 0.05f, 0.00f, -0.20f, -0.40f,
	-0.30f, 0.05f, 0.10f, 0.15f, 0.15f, 0.10f, 0.05f, -0.30f,
	-0.30f, 0.00f, 0.15f, 0.20f, 0.20f, 0.15f, 0.00f, -0.30f,
	-0.30f, 0.05f, 0.15f, 0.20f, 0.20f, 0.15f, 0.05f, -0.30f,
	-0.30f, 0.00f, 0.10f, 0.15f, 0.15f, 0.10f, 0.00f, -0.30f,
	-0.40f, -0.20f, 0.00f, 0.00f, 0.00f, 0.00f, -0.20f, -0.40f,
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
};

// Bishops
static const float WhiteBishopValueTable[64] = {
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
	-0.10f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.05f, 0.10f, 0.10f, 0.05f, 0.00f, -0.10f,
	-0.10f, 0.05f, 0.05f, 0.10f, 0.10f, 0.05f, 0.05f, -0.10f,
	-0.10f, 0.00f, 0.10f, 0.10f, 0.10f, 0.10f, 0.00f, -0.10f,
	-0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, -0.10f,
	-0.10f, 0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.05f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
};
static const float BlackBishopValueTable[64] = {
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
	-0.10f, 0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.05f, -0.10f,
	-0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, -0.10f,
	-0.10f, 0.00f, 0.10f, 0.10f, 0.10f, 0.10f, 0.00f, -0.10f,
	-0.10f, 0.05f, 0.05f, 0.10f, 0.10f, 0.05f, 0.05f, -0.10f,
	-0.10f, 0.00f, 0.05f, 0.10f, 0.10f, 0.05f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
};

// Rooks
static const float WhiteRookValueTable[64] = {
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
	0.05f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	0.00f, 0.00f, 0.00f, 0.05f, 0.05f, 0.00f, 0.00f, 0.00f,
};
static const float BlackRookValueTable[64] = {
	0.00f, 0.00f, 0.00f, 0.05f, 0.05f, 0.00f, 0.00f, 0.00f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	0.05f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.05f,
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
};

// Queens											
static const float WhiteQueenValueTable[64] = {
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
	-0.10f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.10f,
	-0.05f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.05f,
	0.00f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.05f,
	-0.10f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.05f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
};
static const float BlackQueenValueTable[64] = {
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
	-0.10f, 0.00f, 0.05f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.10f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.10f,
	0.00f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.05f,
	-0.10f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
};

// Kings											
static const float WhiteKingMidValueTable[64] = {
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.20f, -0.30f, -0.30f, -0.40f, -0.40f, -0.30f, -0.30f, -0.20f,
	-0.10f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.10f,
	0.20f, 0.20f, 0.00f, 0.00f, 0.00f, 0.00f, 0.20f, 0.20f,
	0.20f, 0.30f, 0.10f, 0.00f, 0.00f, 0.10f, 0.30f, 0.20f,
};
static const float BlackKingMidValueTable[64] = {
	0.20f, 0.30f, 0.10f, 0.00f, 0.00f, 0.10f, 0.30f, 0.20f,
	0.20f, 0.20f, 0.00f, 0.00f, 0.00f, 0.00f, 0.20f, 0.20f,
	-0.10f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.10f,
	-0.20f, -0.30f, -0.30f, -0.40f, -0.40f, -0.30f, -0.30f, -0.20f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
};
static const float WhiteKingEndValueTable[64] = {
	-0.50f, -0.40f, -0.30f, -0.20f, -0.20f, -0.30f, -0.40f, -0.50f,
	-0.30f, -0.20f, -0.10f, 0.00f, 0.00f, -0.10f, -0.20f, -0.30f,
	-0.30f, -0.10f, 0.20f, 0.30f, 0.30f, 0.20f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.30f, 0.40f, 0.40f, 0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.30f, 0.40f, 0.40f, 0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.20f, 0.30f, 0.30f, 0.20f, -0.10f, -0.30f,
	-0.30f, -0.30f, 0.00f, 0.00f, 0.00f, 0.00f, -0.30f, -0.30f,
	-0.50f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.50f,
};
static const float BlackKingEndValueTable[64] = {
	-0.50f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.50f,
	-0.30f, -0.30f, 0.00f, 0.00f, 0.00f, 0.00f, -0.30f, -0.30f,
	-0.30f, -0.10f, 0.20f, 0.30f, 0.30f, 0.20f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.30f, 0.40f, 0.40f, 0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.30f, 0.40f, 0.40f, 0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.20f, 0.30f, 0.30f, 0.20f, -0.10f, -0.30f,
	-0.30f, -0.20f, -0.10f, 0.00f, 0.00f, -0.10f, -0.20f, -0.30f,
	-0.50f, -0.40f, -0.30f, -0.20f, -0.20f, -0.30f, -0.40f, -0.50f,
};


static bool WhiteInEndgame(const Board& board) {
	int minorPieces = 0;
	for (int i = 0; i < 64; i++) {
		switch (board.getPiece(i)) {
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

static bool BlackInEndgame(const Board& board) {
	int minorPieces = 0;
	for (int i = 0; i < 64; i++) {
		switch (board.getPiece(i)) {
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

float Engine::evaluate(const Board& board) {
	float eval = 0.0f;
	for (int i = 0; i < 64; i++) {
		switch (board.getPiece(i)) {
		case Piece::WPawn:
			eval += 1.0f;
			eval += WhitePawnValueTable[i];
			break;
		case Piece::WKnight:
			eval += 3.2f;
			eval += WhiteKnightValueTable[i];
			break;
		case Piece::WBishop:
			eval += 3.3f;
			eval += WhiteBishopValueTable[i];
			break;
		case Piece::WRook:
			eval += 5.0f;
			eval += WhiteRookValueTable[i];
			break;
		case Piece::WQueen:
			eval += 9.0f;
			eval += WhiteQueenValueTable[i];
			break;
		case Piece::WKing:
			eval += 1'000'000.0f;
			eval += WhiteInEndgame(board) ? WhiteKingEndValueTable[i] : WhiteKingMidValueTable[i];
			break;

		case Piece::BPawn:
			eval -= 1.0f;
			eval -= BlackPawnValueTable[i];
			break;
		case Piece::BKnight:
			eval -= 3.2f;
			eval -= BlackKnightValueTable[i];
			break;
		case Piece::BBishop:
			eval -= 3.3f;
			eval -= BlackBishopValueTable[i];
			break;
		case Piece::BRook:
			eval -= 5.0f;
			eval -= BlackRookValueTable[i];
			break;
		case Piece::BQueen:
			eval -= 9.0f;
			eval -= BlackQueenValueTable[i];
			break;
		case Piece::BKing:
			eval -= 1'000'000.0f;
			eval -= BlackInEndgame(board) ? BlackKingEndValueTable[i] : BlackKingMidValueTable[i];
			break;
		}
	}
	return eval;
}
