#pragma once

#include "KrimzLib.h"
#include "Types/Piece.h"
#include "Types/Info.h"


class Board {
public:
	// Piece
	int selectedSquare = -1;
	int wonSquare = -1;
	Move lastMove;

	// Rules
	std::atomic<bool> whiteToPlay = true;
	bool wCanCastleK = true;
	bool wCanCastleQ = true;
	bool bCanCastleK = true;
	bool bCanCastleQ = true;

	Piece pieces[64] = {};

	Board();
	Board(const Board& obj);

	void clear();

	// Loads fen data
	static const String defaultFen;
	void loadFen(const String& fen);

	// Util
	static int toi(int x, int y);
	static bool inBoard(int x, int y);
	static bool isWhite(Piece piece, bool allowNone = false);
	static bool isBlack(Piece piece, bool allowNone = false);

	// Moves
	void getMoves(int pos, std::vector<Move>& outMoves) const;
	void wPawnMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void bPawnMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void wKnightMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void bKnightMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void wBishopMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void bBishopMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void wRookMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void bRookMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void wQueenMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void bQueenMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void wKingMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;
	void bKingMoves(const Piece* pieces, int x, int y, std::vector<Move>& outMoves) const;

	// Plays the move
	void playMove(const Move& move);

	// Logic and input
	void update(kl::window& win);

	// Draws the board
	void draw(kl::image* target) const;
};
