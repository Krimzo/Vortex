#include "Piece/Piece.h"
#include "Position/Position.h"


static void GetWhiteKingMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	if (InBoard(x - 1, y + 1) && position.pieces[ToIndex(x - 1, y + 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y + 1), PieceType::WKing));
	if (InBoard(x + 0, y + 1) && position.pieces[ToIndex(x + 0, y + 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 0, y + 1), PieceType::WKing));
	if (InBoard(x + 1, y + 1) && position.pieces[ToIndex(x + 1, y + 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y + 1), PieceType::WKing));
	if (InBoard(x + 1, y + 0) && position.pieces[ToIndex(x + 1, y + 0)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y + 0), PieceType::WKing));
	if (InBoard(x + 1, y - 1) && position.pieces[ToIndex(x + 1, y - 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y - 1), PieceType::WKing));
	if (InBoard(x + 0, y - 1) && position.pieces[ToIndex(x + 0, y - 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 0, y - 1), PieceType::WKing));
	if (InBoard(x - 1, y - 1) && position.pieces[ToIndex(x - 1, y - 1)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y - 1), PieceType::WKing));
	if (InBoard(x - 1, y + 0) && position.pieces[ToIndex(x - 1, y + 0)].isBlack(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y + 0), PieceType::WKing));

	if (position.castlingWK && !position.pieces[61].exists() && !position.pieces[62].exists()) {
		Position newPosition = position.afterPlaying(60, 62, PieceType::WKing);
		newPosition.pieces[63].type = PieceType::None;
		newPosition.pieces[61].type = PieceType::WRook;
		outPositions.push_back(newPosition);
	}
	if (position.castlingWQ && !position.pieces[57].exists() && !position.pieces[58].exists() && !position.pieces[59].exists()) {
		Position newPosition = position.afterPlaying(60, 58, PieceType::WKing);
		newPosition.pieces[56].type = PieceType::None;
		newPosition.pieces[59].type = PieceType::WRook;
		outPositions.push_back(newPosition);
	}
}

static void GetBlackKingMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) {
	if (InBoard(x - 1, y + 1) && position.pieces[ToIndex(x - 1, y + 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y + 1), PieceType::BKing));
	if (InBoard(x + 0, y + 1) && position.pieces[ToIndex(x + 0, y + 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 0, y + 1), PieceType::BKing));
	if (InBoard(x + 1, y + 1) && position.pieces[ToIndex(x + 1, y + 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y + 1), PieceType::BKing));
	if (InBoard(x + 1, y + 0) && position.pieces[ToIndex(x + 1, y + 0)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y + 0), PieceType::BKing));
	if (InBoard(x + 1, y - 1) && position.pieces[ToIndex(x + 1, y - 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 1, y - 1), PieceType::BKing));
	if (InBoard(x + 0, y - 1) && position.pieces[ToIndex(x + 0, y - 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x + 0, y - 1), PieceType::BKing));
	if (InBoard(x - 1, y - 1) && position.pieces[ToIndex(x - 1, y - 1)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y - 1), PieceType::BKing));
	if (InBoard(x - 1, y + 0) && position.pieces[ToIndex(x - 1, y + 0)].isWhite(true)) outPositions.push_back(position.afterPlaying(ToIndex(x, y), ToIndex(x - 1, y + 0), PieceType::BKing));

	if (position.castlingBK && !position.pieces[5].exists() && !position.pieces[6].exists()) {
		Position newPosition = position.afterPlaying(4, 6, PieceType::BKing);
		newPosition.pieces[7].type = PieceType::None;
		newPosition.pieces[5].type = PieceType::BRook;
		outPositions.push_back(newPosition);
	}
	if (position.castlingBQ && !position.pieces[1].exists() && !position.pieces[2].exists() && !position.pieces[3].exists()) {
		Position newPosition = position.afterPlaying(4, 2, PieceType::BKing);
		newPosition.pieces[0].type = PieceType::None;
		newPosition.pieces[3].type = PieceType::BRook;
		outPositions.push_back(newPosition);
	}
}

void Piece::getKingMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const {
	if (this->isWhite()) {
		GetWhiteKingMoves(position, x, y, outPositions);
	}
	else {
		GetBlackKingMoves(position, x, y, outPositions);
	}
}
