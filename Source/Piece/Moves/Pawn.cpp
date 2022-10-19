#include "Piece/Piece.h"
#include "Position/Position.h"


static void GetWhitePawnMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	if (InBoard(x, y - 1) && !position.pieces[ToIndex(x, y - 1)].exists()) {
		outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x, y - 1), (y == 1) ? PieceType::WQueen : PieceType::WPawn));

		if (y == 6 && !position.pieces[ToIndex(x, y - 2)].exists()) {
			outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x, y - 2), PieceType::WPawn));
		}
	}

	if (InBoard(x - 1, y - 1) && position.pieces[ToIndex(x - 1, y - 1)].isBlack()) {
		outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y - 1), (y == 1) ? PieceType::WQueen : PieceType::WPawn));
	}
	if (InBoard(x + 1, y - 1) && position.pieces[ToIndex(x + 1, y - 1)].isBlack()) {
		outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y - 1), (y == 1) ? PieceType::WQueen : PieceType::WPawn));
	}
}

static void GetBlackPawnMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	if (InBoard(x, y + 1) && !position.pieces[ToIndex(x, y + 1)].exists()) {
		outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x, y + 1), (y == 6) ? PieceType::BQueen : PieceType::BPawn));

		if (y == 1 && !position.pieces[ToIndex(x, y + 2)].exists()) {
			outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x, y + 2), PieceType::BPawn));
		}
	}

	if (InBoard(x - 1, y + 1) && position.pieces[ToIndex(x - 1, y + 1)].isWhite()) {
		outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y + 1), (y == 6) ? PieceType::BQueen : PieceType::BPawn));
	}
	if (InBoard(x + 1, y + 1) && position.pieces[ToIndex(x + 1, y + 1)].isWhite()) {
		outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y + 1), (y == 6) ? PieceType::BQueen : PieceType::BPawn));
	}
}

void Piece::getPawnMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const {
	if (this->isWhite()) {
		GetWhitePawnMoves(position, x, y, outPositions);
	}
	else {
		GetBlackPawnMoves(position, x, y, outPositions);
	}
}
