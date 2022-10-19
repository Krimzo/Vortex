#include "Piece/Piece.h"
#include "Position/Position.h"


static void GetWhiteBishopMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x + i, y + i);
		if (InBoard(x + i, y + i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WBishop));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WBishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x - i, y + i);
		if (InBoard(x - i, y + i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WBishop));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WBishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x + i, y - i);
		if (InBoard(x + i, y - i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WBishop));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WBishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x - i, y - i);
		if (InBoard(x - i, y - i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WBishop));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::WBishop));
				break;
			}
			else {
				break;
			}
		}
	}
}

static void GetBlackBishopMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x + i, y + i);
		if (InBoard(x + i, y + i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BBishop));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BBishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x - i, y + i);
		if (InBoard(x - i, y + i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BBishop));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BBishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x + i, y - i);
		if (InBoard(x + i, y - i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BBishop));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BBishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = ToIndex(x - i, y - i);
		if (InBoard(x - i, y - i)) {
			if (!position.pieces[index].exists()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BBishop));
			}
			else if (position.pieces[index].isBlack()) {
				outPositions.push_back(position.afterPlaying(ToIndex(x, y), index, PieceType::BBishop));
				break;
			}
			else {
				break;
			}
		}
	}
}

void Piece::getBishopMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const {
	if (this->isWhite()) {
		GetWhiteBishopMoves(position, x, y, outPositions);
	}
	else {
		GetBlackBishopMoves(position, x, y, outPositions);
	}
}
