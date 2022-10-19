#include "Piece/Piece.h"
#include "Position/Position.h"


static void GetWhiteRookMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x + i, y);
		if (InBoard(x + i, y)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WRook));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WRook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x - i, y);
		if (InBoard(x - i, y)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WRook));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WRook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x, y + i);
		if (InBoard(x, y + i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WRook));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WRook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x, y - i);
		if (InBoard(x, y - i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WRook));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WRook));
				break;
			}
			else {
				break;
			}
		}
	}
}

static void GetBlackRookMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x + i, y);
		if (InBoard(x + i, y)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BRook));
			}
			else if (position.pieces[index].isWhite()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BRook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x - i, y);
		if (InBoard(x - i, y)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BRook));
			}
			else if (position.pieces[index].isWhite()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BRook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x, y + i);
		if (InBoard(x, y + i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BRook));
			}
			else if (position.pieces[index].isWhite()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BRook));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x, y - i);
		if (InBoard(x, y - i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BRook));
			}
			else if (position.pieces[index].isWhite()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BRook));
				break;
			}
			else {
				break;
			}
		}
	}
}

void Piece::getRookMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const {
	if (this->isWhite()) {
		GetWhiteRookMoves(position, x, y, outPositions);
	}
	else {
		GetBlackRookMoves(position, x, y, outPositions);
	}
}
