#include "Board/Board.h"


int Board::ToIndex(int x, int y) {
	return y * 8 + x;
}

bool Board::InBoard(int x, int y) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		return true;
	}
	return false;
}

bool Board::IsWhite(Piece piece, bool allowNone) {
	return allowNone ? int(piece) >= 0 : int(piece) > 0;
}

bool Board::IsBlack(Piece piece, bool allowNone) {
	return allowNone ? int(piece) <= 0 : int(piece) < 0;
}

void Board::getSquareMoves(int position, std::vector<Move>& buffer) const {
	const int x = position % 8;
	const int y = position / 8;

	switch (m_Pieces[position]) {
	case Piece::WPawn:
		getPawnMoves(true, m_Pieces, x, y, buffer);
		break;
	case Piece::BPawn:
		getPawnMoves(false, m_Pieces, x, y, buffer);
		break;

	case Piece::WKnight:
		getKnightMoves(true, m_Pieces, x, y, buffer);
		break;
	case Piece::BKnight:
		getKnightMoves(false, m_Pieces, x, y, buffer);
		break;

	case Piece::WBishop:
		getBishopMoves(true, m_Pieces, x, y, buffer);
		break;
	case Piece::BBishop:
		getBishopMoves(false, m_Pieces, x, y, buffer);
		break;

	case Piece::WRook:
		getRookMoves(true, m_Pieces, x, y, buffer);
		break;
	case Piece::BRook:
		getRookMoves(false, m_Pieces, x, y, buffer);
		break;

	case Piece::WQueen:
		getQueenMoves(true, m_Pieces, x, y, buffer);
		break;
	case Piece::BQueen:
		getQueenMoves(false, m_Pieces, x, y, buffer);
		break;

	case Piece::WKing:
		getKingMoves(true, m_Pieces, x, y, buffer);
		break;
	case Piece::BKing:
		getKingMoves(false, m_Pieces, x, y, buffer);
		break;
	}
}
