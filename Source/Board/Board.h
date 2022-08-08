#pragma once

#include "KrimzLib.h"
#include "Board/Types.h"


class Board {
	kl::Atomic<bool> m_MovePlaying = false;

	int m_SelectedSquare = -1;
	int m_WonSquare = -1;
	Move m_LastMove = {};

	bool m_WhiteToPlay = true;
	bool m_CastleRights[4] = { true, true, true, true };

	Piece m_Pieces[64] = {};

	static const kl::Color defaultLight;
	static const kl::Color defaultDark;
	static const kl::Color selectedLigt;
	static const kl::Color selectedDark;
	static const kl::Color lastMoveLight;
	static const kl::Color lastMoveDark;
	static const kl::Color wonSquareLigt;
	static const kl::Color wonSquareDark;

	static const kl::Image icons[12];

public:
	static const kl::String DefaultFEN;

	static int ToIndex(int x, int y);
	static bool InBoard(int x, int y);
	static bool IsWhite(Piece piece, bool allowNone = false);
	static bool IsBlack(Piece piece, bool allowNone = false);

	Board();
	Board(const Board& board);
	Board& operator=(const Board& board);

	Piece getPiece(int index) const;

	void clearPieces();

	void loadFEN(const kl::String& fen);

	void playMove(const Move& move);

	void playerPlay(kl::Window& window, int clickedIndex);
	void enginePlay(kl::Window& window);

	void drawToImage(kl::Image& target) const;

	void getSquareMoves(int position, kl::Vector<Move>& buffer) const;

	void getPawnMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const;
	void getKnightMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const;
	void getBishopMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const;
	void getRookMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const;
	void getQueenMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const;
	void getKingMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const;
};
