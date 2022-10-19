#pragma once

#include "Piece/Piece.h"


using FEN = kl::String;

inline const FEN DefaultFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";


bool InBoard(int x, int y);

int ToIndex(int x, int y);

class Position {
public:
	Piece pieces[64] = {};
	bool whiteToPlay = true;

	bool castlingWK = true;
	bool castlingWQ = true;
	bool castlingBK = true;
	bool castlingBQ = true;

	float evaluation = 0;
	kl::Int2 lastPlayedMove = kl::Int2::Splash(-1);

	Position();

	Position(const FEN& fen);

	void loadFEN(const FEN& fen);

	void clear();

	Position afterPlaying(int fromIndex, int toIndex, PieceType newType) const;

	int getWinState() const;
};
