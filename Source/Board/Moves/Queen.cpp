#include "Board/Board.h"


static void GetWhiteQueenMoves(const Board& board, const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	kl::Vector<Move> bishopMoves;
	board.getBishopMoves(true, pieces, x, y, bishopMoves);

	for (auto& move : bishopMoves) {
		move.to.piece = Piece::WQueen;
		buffer.push_back(move);
	}

	kl::Vector<Move> rookMoves;
	board.getRookMoves(true, pieces, x, y, rookMoves);

	for (auto& move : rookMoves) {
		move.to.piece = Piece::WQueen;
		buffer.push_back(move);
	}
}

static void GetBlackQueenMoves(const Board& board, const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	kl::Vector<Move> bishopMoves;
	board.getBishopMoves(false, pieces, x, y, bishopMoves);

	for (auto& move : bishopMoves) {
		move.to.piece = Piece::BQueen;
		buffer.push_back(move);
	}

	kl::Vector<Move> rookMoves;
	board.getRookMoves(false, pieces, x, y, rookMoves);

	for (auto& move : rookMoves) {
		move.to.piece = Piece::BQueen;
		buffer.push_back(move);
	}
}

void Board::getQueenMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const {
	buffer.clear();
	buffer.reserve(27);

	if (isWhite) {
		GetWhiteQueenMoves(*this, pieces, x, y, buffer);
	}
	else {
		GetBlackQueenMoves(*this, pieces, x, y, buffer);
	}
}
