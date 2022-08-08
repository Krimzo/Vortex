#include "Board/Board.h"


static void GetWhiteKnightMoves(const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	if (Board::InBoard(x + 1, y + 2) && Board::IsBlack(pieces[Board::ToIndex(x + 1, y + 2)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y + 2), Piece::WKnight)));
	if (Board::InBoard(x - 1, y + 2) && Board::IsBlack(pieces[Board::ToIndex(x - 1, y + 2)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y + 2), Piece::WKnight)));
	if (Board::InBoard(x + 1, y - 2) && Board::IsBlack(pieces[Board::ToIndex(x + 1, y - 2)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y - 2), Piece::WKnight)));
	if (Board::InBoard(x - 1, y - 2) && Board::IsBlack(pieces[Board::ToIndex(x - 1, y - 2)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y - 2), Piece::WKnight)));
	if (Board::InBoard(x + 2, y + 1) && Board::IsBlack(pieces[Board::ToIndex(x + 2, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 2, y + 1), Piece::WKnight)));
	if (Board::InBoard(x + 2, y - 1) && Board::IsBlack(pieces[Board::ToIndex(x + 2, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 2, y - 1), Piece::WKnight)));
	if (Board::InBoard(x - 2, y + 1) && Board::IsBlack(pieces[Board::ToIndex(x - 2, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 2, y + 1), Piece::WKnight)));
	if (Board::InBoard(x - 2, y - 1) && Board::IsBlack(pieces[Board::ToIndex(x - 2, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 2, y - 1), Piece::WKnight)));
}

static void GetBlackKnightMoves(const Piece* pieces, const int x, const int y, kl::Vector<Move>& buffer) {
	if (Board::InBoard(x + 1, y + 2) && Board::IsWhite(pieces[Board::ToIndex(x + 1, y + 2)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y + 2), Piece::BKnight)));
	if (Board::InBoard(x - 1, y + 2) && Board::IsWhite(pieces[Board::ToIndex(x - 1, y + 2)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y + 2), Piece::BKnight)));
	if (Board::InBoard(x + 1, y - 2) && Board::IsWhite(pieces[Board::ToIndex(x + 1, y - 2)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 1, y - 2), Piece::BKnight)));
	if (Board::InBoard(x - 1, y - 2) && Board::IsWhite(pieces[Board::ToIndex(x - 1, y - 2)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 1, y - 2), Piece::BKnight)));
	if (Board::InBoard(x + 2, y + 1) && Board::IsWhite(pieces[Board::ToIndex(x + 2, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 2, y + 1), Piece::BKnight)));
	if (Board::InBoard(x + 2, y - 1) && Board::IsWhite(pieces[Board::ToIndex(x + 2, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x + 2, y - 1), Piece::BKnight)));
	if (Board::InBoard(x - 2, y + 1) && Board::IsWhite(pieces[Board::ToIndex(x - 2, y + 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 2, y + 1), Piece::BKnight)));
	if (Board::InBoard(x - 2, y - 1) && Board::IsWhite(pieces[Board::ToIndex(x - 2, y - 1)], true)) buffer.push_back(Move(Square(Board::ToIndex(x, y), Piece::None), Square(Board::ToIndex(x - 2, y - 1), Piece::BKnight)));
}

void Board::getKnightMoves(bool isWhite, const Piece* pieces, int x, int y, kl::Vector<Move>& buffer) const {
	buffer.clear();
	buffer.reserve(8);

	if (isWhite) {
		GetWhiteKnightMoves(pieces, x, y, buffer);
	}
	else {
		GetBlackKnightMoves(pieces, x, y, buffer);
	}
}
