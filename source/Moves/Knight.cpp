#include "Board/Board.h"


void Board::wKnightMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(8);

	if (inBoard(x + 1, y + 2) && isBlack(pieces[toi(x + 1, y + 2)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y + 2), Piece::WKnight)));
	if (inBoard(x - 1, y + 2) && isBlack(pieces[toi(x - 1, y + 2)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y + 2), Piece::WKnight)));
	if (inBoard(x + 1, y - 2) && isBlack(pieces[toi(x + 1, y - 2)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y - 2), Piece::WKnight)));
	if (inBoard(x - 1, y - 2) && isBlack(pieces[toi(x - 1, y - 2)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y - 2), Piece::WKnight)));
	if (inBoard(x + 2, y + 1) && isBlack(pieces[toi(x + 2, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 2, y + 1), Piece::WKnight)));
	if (inBoard(x + 2, y - 1) && isBlack(pieces[toi(x + 2, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 2, y - 1), Piece::WKnight)));
	if (inBoard(x - 2, y + 1) && isBlack(pieces[toi(x - 2, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 2, y + 1), Piece::WKnight)));
	if (inBoard(x - 2, y - 1) && isBlack(pieces[toi(x - 2, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 2, y - 1), Piece::WKnight)));
}

void Board::bKnightMoves(const Piece* pieces, const int x, const int y, std::vector<Move>& outMoves) const {
	outMoves.resize(0);
	outMoves.reserve(8);

	if (inBoard(x + 1, y + 2) && isWhite(pieces[toi(x + 1, y + 2)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y + 2), Piece::BKnight)));
	if (inBoard(x - 1, y + 2) && isWhite(pieces[toi(x - 1, y + 2)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y + 2), Piece::BKnight)));
	if (inBoard(x + 1, y - 2) && isWhite(pieces[toi(x + 1, y - 2)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 1, y - 2), Piece::BKnight)));
	if (inBoard(x - 1, y - 2) && isWhite(pieces[toi(x - 1, y - 2)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 1, y - 2), Piece::BKnight)));
	if (inBoard(x + 2, y + 1) && isWhite(pieces[toi(x + 2, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 2, y + 1), Piece::BKnight)));
	if (inBoard(x + 2, y - 1) && isWhite(pieces[toi(x + 2, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x + 2, y - 1), Piece::BKnight)));
	if (inBoard(x - 2, y + 1) && isWhite(pieces[toi(x - 2, y + 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 2, y + 1), Piece::BKnight)));
	if (inBoard(x - 2, y - 1) && isWhite(pieces[toi(x - 2, y - 1)], true)) outMoves.push_back(Move(Square(toi(x, y), Piece::None), Square(toi(x - 2, y - 1), Piece::BKnight)));
}
