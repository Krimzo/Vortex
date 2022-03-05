#include "Chess/Piece.h"


// Returns piece type
int PieceType(Piece piece) {
	switch (piece) {
	case WPawn:
		return 1;
	case WKnight:
		return 1;
	case WBishop:
		return 1;
	case WRook:
		return 1;
	case WQueen:
		return 1;
	case WKing:
		return 1;

	case BPawn:
		return -1;
	case BKnight:
		return -1;
	case BBishop:
		return -1;
	case BRook:
		return -1;
	case BQueen:
		return -1;
	case BKing:
		return -1;

	default:
		return 0;
	}
}
