#include "Piece/Piece.h"
#include "Position/Position.h"


static const kl::Image PieceIcons[12] = {
	{ "resource/w_pawn.png" },
	{ "resource/w_knight.png" },
	{ "resource/w_bishop.png" },
	{ "resource/w_rook.png" },
	{ "resource/w_queen.png" },
	{ "resource/w_king.png" },
	{ "resource/b_pawn.png" },
	{ "resource/b_knight.png" },
	{ "resource/b_bishop.png" },
	{ "resource/b_rook.png" },
	{ "resource/b_queen.png" },
	{ "resource/b_king.png" }
};


Piece::Piece() {}

Piece::Piece(PieceType type) : type(type) {}

const kl::Image* Piece::getIcon() const {
	switch (type) {
	case WPawn:
		return &PieceIcons[0];
	case WKnight:
		return &PieceIcons[1];
	case WBishop:
		return &PieceIcons[2];
	case WRook:
		return &PieceIcons[3];
	case WQueen:
		return &PieceIcons[4];
	case WKing:
		return &PieceIcons[5];

	case BPawn:
		return &PieceIcons[6];
	case BKnight:
		return &PieceIcons[7];
	case BBishop:
		return &PieceIcons[8];
	case BRook:
		return &PieceIcons[9];
	case BQueen:
		return &PieceIcons[10];
	case BKing:
		return &PieceIcons[11];

	case None:
	default:
		return nullptr;
	}
}

bool Piece::exists() const {
	return (bool) type;
}

bool Piece::isWhite(bool allowNone) const {
	return (type > 64 && type < 91) || (allowNone && !type);
}

bool Piece::isBlack(bool allowNone) const {
	return (type > 96 && type < 123) || (allowNone && !type);
}

void Piece::getMoves(const Position& position, int pieceIndex, kl::Vector<Position>& outPositions) const {
	const int x = pieceIndex % 8; const int y = pieceIndex / 8;

	switch (type) {
	case PieceType::WPawn:
	case PieceType::BPawn:
		getPawnMoves(position, x, y, outPositions);
		break;

	case PieceType::WKnight:
	case PieceType::BKnight:
		getKnightMoves(position, x, y, outPositions);
		break;

	case PieceType::WBishop:
	case PieceType::BBishop:
		getBishopMoves(position, x, y, outPositions);
		break;

	case PieceType::WRook:
	case PieceType::BRook:
		getRookMoves(position, x, y, outPositions);
		break;

	case PieceType::WQueen:
	case PieceType::BQueen:
		getQueenMoves(position, x, y, outPositions);
		break;

	case PieceType::WKing:
	case PieceType::BKing:
		getKingMoves(position, x, y, outPositions);
		break;
	}
}
