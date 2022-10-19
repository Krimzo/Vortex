#include "Piece/Piece.h"
#include "Position/Position.h"


static void GetWhiteQueenMoves(const Piece& piece, const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	kl::Vector<Position> bishopPositions = {};
	piece.getBishopMoves(position, x, y, bishopPositions);

	for (auto& position : bishopPositions) {
		position.pieces[position.lastPlayedMove.y] = PieceType::WQueen;
		outPositions.push_back(position);
	}

	kl::Vector<Position> rookPositions;
	piece.getRookMoves(position, x, y, rookPositions);

	for (auto& position : rookPositions) {
		position.pieces[position.lastPlayedMove.y] = PieceType::WQueen;
		outPositions.push_back(position);
	}
}

static void GetBlackQueenMoves(const Piece& piece, const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	kl::Vector<Position> bishopPositions = {};
	piece.getBishopMoves(position, x, y, bishopPositions);

	for (auto& position : bishopPositions) {
		position.pieces[position.lastPlayedMove.y] = PieceType::BQueen;
		outPositions.push_back(position);
	}

	kl::Vector<Position> rookPositions;
	piece.getRookMoves(position, x, y, rookPositions);

	for (auto& position : rookPositions) {
		position.pieces[position.lastPlayedMove.y] = PieceType::BQueen;
		outPositions.push_back(position);
	}
}

void Piece::getQueenMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const {
	if (this->isWhite()) {
		GetWhiteQueenMoves(*this, position, x, y, outPositions);
	}
	else {
		GetBlackQueenMoves(*this, position, x, y, outPositions);
	}
}
