#include "Board/Board.h"


void Board::wQueenMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	std::vector<Move> bishMoves;
	wBishopMoves(pieces, x, y, bishMoves);
	std::vector<Move> rookMoves;
	wRookMoves(pieces, x, y, rookMoves);

	outMoves.resize(0);
	outMoves.reserve(27);

	for (auto& m : bishMoves) {
		m.to.piece = Piece::WQueen;
		outMoves.push_back(m);
	}
	for (auto& m : rookMoves) {
		m.to.piece = Piece::WQueen;
		outMoves.push_back(m);
	}
}

void Board::bQueenMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	std::vector<Move> bishMoves;
	bBishopMoves(pieces, x, y, bishMoves);
	std::vector<Move> rookMoves;
	bRookMoves(pieces, x, y, rookMoves);

	outMoves.resize(0);
	outMoves.reserve(27);

	for (auto& m : bishMoves) {
		m.to.piece = Piece::BQueen;
		outMoves.push_back(m);
	}
	for (auto& m : rookMoves) {
		m.to.piece = Piece::BQueen;
		outMoves.push_back(m);
	}
}
