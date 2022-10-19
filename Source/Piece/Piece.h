#pragma once

#include "KrimzLib.h"


class Position;

enum PieceType {
	None = 0,

	WPawn = 'P',
	WKnight = 'N',
	WBishop = 'B',
	WRook = 'R',
	WQueen = 'Q',
	WKing = 'K',

	BPawn = 'p',
	BKnight = 'n',
	BBishop = 'b',
	BRook = 'r',
	BQueen = 'q',
	BKing = 'k',
};

class Piece {
public:
	PieceType type = {};

	Piece();

	Piece(PieceType type);

	const kl::Image* getIcon() const;

	bool exists() const;
	bool isWhite(bool allowNone = false) const;
	bool isBlack(bool allowNone = false) const;

	void getMoves(const Position& position, int pieceIndex, kl::Vector<Position>& outPositions) const;
	void getPawnMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const;
	void getKnightMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const;
	void getBishopMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const;
	void getRookMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const;
	void getQueenMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const;
	void getKingMoves(const Position& position, const int x, const int y, kl::Vector<Position>& outPositions) const;
};
