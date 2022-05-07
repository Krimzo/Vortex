#include "Board/Board.h"


// Util
int  Board::toi(int x, int y) {
	return y * 8 + x;
}
bool Board::inBoard(int x, int y) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		return true;
	}
	return false;
}
bool Board::isWhite(Piece piece, bool allowNone) {
	if (allowNone) {
		return int(piece) >= 0;
	}
	return int(piece) > 0;
}
bool Board::isBlack(Piece piece, bool allowNone) {
	if (allowNone) {
		return int(piece) <= 0;
	}
	return int(piece) < 0;
}

// Returns possible piece moves
void Board::getMoves(int pos, std::vector<Move>& outMoves) const {
	const int x = pos % 8;
	const int y = pos / 8;

	switch (pieces[pos]) {
	case Piece::WPawn:
		wPawnMoves(pieces, x, y, outMoves);
		break;
	case Piece::BPawn:
		bPawnMoves(pieces, x, y, outMoves);
		break;

	case Piece::WKnight:
		wKnightMoves(pieces, x, y, outMoves);
		break;
	case Piece::BKnight:
		bKnightMoves(pieces, x, y, outMoves);
		break;

	case Piece::WBishop:
		wBishopMoves(pieces, x, y, outMoves);
		break;
	case Piece::BBishop:
		bBishopMoves(pieces, x, y, outMoves);
		break;

	case Piece::WRook:
		wRookMoves(pieces, x, y, outMoves);
		break;
	case Piece::BRook:
		bRookMoves(pieces, x, y, outMoves);
		break;

	case Piece::WQueen:
		wQueenMoves(pieces, x, y, outMoves);
		break;
	case Piece::BQueen:
		bQueenMoves(pieces, x, y, outMoves);
		break;

	case Piece::WKing:
		wKingMoves(pieces, x, y, outMoves);
		break;
	case Piece::BKing:
		bKingMoves(pieces, x, y, outMoves);
		break;
	}
}
