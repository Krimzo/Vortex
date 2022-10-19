#include "Piece/Piece.h"
#include "Position/Position.h"


static void GetWhiteKnightMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	if (InBoard(x + 1, y + 2) && position.pieces[ToIndex(x + 1, y + 2)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y + 2), PieceType::WKnight));
	if (InBoard(x - 1, y + 2) && position.pieces[ToIndex(x - 1, y + 2)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y + 2), PieceType::WKnight));
	if (InBoard(x + 1, y - 2) && position.pieces[ToIndex(x + 1, y - 2)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y - 2), PieceType::WKnight));
	if (InBoard(x - 1, y - 2) && position.pieces[ToIndex(x - 1, y - 2)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y - 2), PieceType::WKnight));
	if (InBoard(x + 2, y + 1) && position.pieces[ToIndex(x + 2, y + 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 2, y + 1), PieceType::WKnight));
	if (InBoard(x + 2, y - 1) && position.pieces[ToIndex(x + 2, y - 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 2, y - 1), PieceType::WKnight));
	if (InBoard(x - 2, y + 1) && position.pieces[ToIndex(x - 2, y + 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 2, y + 1), PieceType::WKnight));
	if (InBoard(x - 2, y - 1) && position.pieces[ToIndex(x - 2, y - 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 2, y - 1), PieceType::WKnight));
}

static void GetBlackKnightMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	if (InBoard(x + 1, y + 2) && position.pieces[ToIndex(x + 1, y + 2)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y + 2), PieceType::BKnight));
	if (InBoard(x - 1, y + 2) && position.pieces[ToIndex(x - 1, y + 2)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y + 2), PieceType::BKnight));
	if (InBoard(x + 1, y - 2) && position.pieces[ToIndex(x + 1, y - 2)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y - 2), PieceType::BKnight));
	if (InBoard(x - 1, y - 2) && position.pieces[ToIndex(x - 1, y - 2)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y - 2), PieceType::BKnight));
	if (InBoard(x + 2, y + 1) && position.pieces[ToIndex(x + 2, y + 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 2, y + 1), PieceType::BKnight));
	if (InBoard(x + 2, y - 1) && position.pieces[ToIndex(x + 2, y - 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 2, y - 1), PieceType::BKnight));
	if (InBoard(x - 2, y + 1) && position.pieces[ToIndex(x - 2, y + 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 2, y + 1), PieceType::BKnight));
	if (InBoard(x - 2, y - 1) && position.pieces[ToIndex(x - 2, y - 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 2, y - 1), PieceType::BKnight));
}

void Piece::getKnightMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const {
	if (this->isWhite()) {
		GetWhiteKnightMoves(position, x, y, outPositions);
	}
	else {
		GetBlackKnightMoves(position, x, y, outPositions);
	}
}
