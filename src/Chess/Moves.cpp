#include "Chess/Board.h"


// XY to I
int ToI(int x, int y) {
	return y * 8 + x;
}

// Coords in board check
bool InBoard(int x, int y) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		return true;
	}
	return false;
}

// Special piece type moves
std::vector<Move> PawnMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<Move> moves;
	if (pieces[pos].color() > 0) {
		// Moving
		if (InBoard(x, y - 1) && pieces[ToI(x, y - 1)].color() == 0) {
			// Moving 1 y up
			moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x, y - 1), (y == 1) ? Piece::Type::WQueen : Piece::Type::WPawn)));

			// Moving 2 y up
			if (y == 6 && pieces[ToI(x, y - 2)].color() == 0) {
				moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x, y - 2), Piece::Type::WPawn)));
			}
		}

		// Eating
		// Left
		if (InBoard(x - 1, y - 1) && pieces[ToI(x - 1, y - 1)].color() < 0) {
			moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y - 1), (y == 1) ? Piece::Type::WQueen : Piece::Type::WPawn)));
		}
		// Right
		if (InBoard(x + 1, y - 1) && pieces[ToI(x + 1, y - 1)].color() < 0) {
			moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y - 1), (y == 1) ? Piece::Type::WQueen : Piece::Type::WPawn)));
		}
	}
	else {
		// Moving
		if (InBoard(x, y + 1) && pieces[ToI(x, y + 1)].color() == 0) {
			// Moving 1 y up
			moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x, y + 1), (y == 6) ? Piece::Type::BQueen : Piece::Type::BPawn)));

			// Moving 2 y up
			if (y == 1 && pieces[ToI(x, y + 2)].color() == 0) {
				moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x, y + 2), Piece::Type::BPawn)));
			}
		}

		// Eating
		// Left
		if (InBoard(x - 1, y + 1) && pieces[ToI(x - 1, y + 1)].color() > 0) {
			moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y + 1), (y == 6) ? Piece::Type::BQueen : Piece::Type::BPawn)));
		}
		// Right
		if (InBoard(x + 1, y + 1) && pieces[ToI(x + 1, y + 1)].color() > 0) {
			moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y + 1), (y == 6) ? Piece::Type::BQueen : Piece::Type::BPawn)));
		}
	}
	return moves;
}
std::vector<Move> KnightMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<Move> moves;
	if (pieces[pos].color() > 0) {
		if (InBoard(x + 1, y + 2) && pieces[ToI(x + 1, y + 2)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y + 2), Piece::Type::WKnight)));
		if (InBoard(x - 1, y + 2) && pieces[ToI(x - 1, y + 2)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y + 2), Piece::Type::WKnight)));
		if (InBoard(x + 1, y - 2) && pieces[ToI(x + 1, y - 2)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y - 2), Piece::Type::WKnight)));
		if (InBoard(x - 1, y - 2) && pieces[ToI(x - 1, y - 2)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y - 2), Piece::Type::WKnight)));
		if (InBoard(x + 2, y + 1) && pieces[ToI(x + 2, y + 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 2, y + 1), Piece::Type::WKnight)));
		if (InBoard(x + 2, y - 1) && pieces[ToI(x + 2, y - 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 2, y - 1), Piece::Type::WKnight)));
		if (InBoard(x - 2, y + 1) && pieces[ToI(x - 2, y + 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 2, y + 1), Piece::Type::WKnight)));
		if (InBoard(x - 2, y - 1) && pieces[ToI(x - 2, y - 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 2, y - 1), Piece::Type::WKnight)));
	}
	else {
		if (InBoard(x + 1, y + 2) && pieces[ToI(x + 1, y + 2)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y + 2), Piece::Type::BKnight)));
		if (InBoard(x - 1, y + 2) && pieces[ToI(x - 1, y + 2)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y + 2), Piece::Type::BKnight)));
		if (InBoard(x + 1, y - 2) && pieces[ToI(x + 1, y - 2)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y - 2), Piece::Type::BKnight)));
		if (InBoard(x - 1, y - 2) && pieces[ToI(x - 1, y - 2)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y - 2), Piece::Type::BKnight)));
		if (InBoard(x + 2, y + 1) && pieces[ToI(x + 2, y + 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 2, y + 1), Piece::Type::BKnight)));
		if (InBoard(x + 2, y - 1) && pieces[ToI(x + 2, y - 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 2, y - 1), Piece::Type::BKnight)));
		if (InBoard(x - 2, y + 1) && pieces[ToI(x - 2, y + 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 2, y + 1), Piece::Type::BKnight)));
		if (InBoard(x - 2, y - 1) && pieces[ToI(x - 2, y - 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 2, y - 1), Piece::Type::BKnight)));
	}
	return moves;
}
std::vector<Move> BishopMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<Move> moves;
	if (pieces[pos].color() > 0) {
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x + i, y + i);
			if (InBoard(x + i, y + i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WBishop)));
				}
				else if (pieces[ind].color() < 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WBishop)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x - i, y + i);
			if (InBoard(x - i, y + i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WBishop)));
				}
				else if (pieces[ind].color() < 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WBishop)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x + i, y - i);
			if (InBoard(x + i, y - i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WBishop)));
				}
				else if (pieces[ind].color() < 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WBishop)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x - i, y - i);
			if (InBoard(x - i, y - i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WBishop)));
				}
				else if (pieces[ind].color() < 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WBishop)));
					break;
				}
				else {
					break;
				}
			}
		}
	}
	else {
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x + i, y + i);
			if (InBoard(x + i, y + i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BBishop)));
				}
				else if (pieces[ind].color() > 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BBishop)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x - i, y + i);
			if (InBoard(x - i, y + i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BBishop)));
				}
				else if (pieces[ind].color() > 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BBishop)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x + i, y - i);
			if (InBoard(x + i, y - i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BBishop)));
				}
				else if (pieces[ind].color() > 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BBishop)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x - i, y - i);
			if (InBoard(x - i, y - i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BBishop)));
				}
				else if (pieces[ind].color() > 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BBishop)));
					break;
				}
				else {
					break;
				}
			}
		}
	}
	return moves;
}
std::vector<Move> RookMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<Move> moves;
	if (pieces[pos].color() > 0) {
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x + i, y);
			if (InBoard(x + i, y)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WRook)));
				}
				else if (pieces[ind].color() < 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WRook)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x - i, y);
			if (InBoard(x - i, y)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WRook)));
				}
				else if (pieces[ind].color() < 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WRook)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x, y + i);
			if (InBoard(x, y + i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WRook)));
				}
				else if (pieces[ind].color() < 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WRook)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x, y - i);
			if (InBoard(x, y - i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WRook)));
				}
				else if (pieces[ind].color() < 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::WRook)));
					break;
				}
				else {
					break;
				}
			}
		}
	}
	else {
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x + i, y);
			if (InBoard(x + i, y)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BRook)));
				}
				else if (pieces[ind].color() > 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BRook)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x - i, y);
			if (InBoard(x - i, y)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BRook)));
				}
				else if (pieces[ind].color() > 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BRook)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x, y + i);
			if (InBoard(x, y + i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BRook)));
				}
				else if (pieces[ind].color() > 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BRook)));
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const int ind = ToI(x, y - i);
			if (InBoard(x, y - i)) {
				if (pieces[ind].color() == 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BRook)));
				}
				else if (pieces[ind].color() > 0) {
					moves.push_back(Move(Square(pos, Piece::Type::None), Square(ind, Piece::Type::BRook)));
					break;
				}
				else {
					break;
				}
			}
		}
	}
	return moves;
}
std::vector<Move> QueenMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	// Getting bishop and rook moves
	const std::vector<Move> bishMoves = BishopMoves(pieces, pos);
	const std::vector<Move> rookMoves = RookMoves(pieces, pos);

	// Building queen moves
	const Piece::Type queenType = (pieces[pos].color() > 0) ? Piece::Type::WQueen : Piece::Type::BQueen;
	std::vector<Move> moves(bishMoves.size() + rookMoves.size());
	for (int i = 0; i < moves.size(); i++) {
		if (i < bishMoves.size()) {
			moves[i].from.index = bishMoves[i].from.index;
			moves[i].from.piece = Piece::Type::None;
			moves[i].to.index = bishMoves[i].to.index;
			moves[i].to.piece = queenType;
		}
		else {
			moves[i].from.index = rookMoves[i - bishMoves.size()].from.index;
			moves[i].from.piece = Piece::Type::None;
			moves[i].to.index = rookMoves[i - bishMoves.size()].to.index;
			moves[i].to.piece = queenType;
		}
	}
	return moves;
}
std::vector<Move> KingMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<Move> moves;
	if (pieces[pos].color() > 0) {
		if (InBoard(x - 1, y + 1) && pieces[ToI(x - 1, y + 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y + 1), Piece::Type::WKing)));
		if (InBoard(x + 0, y + 1) && pieces[ToI(x + 0, y + 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 0, y + 1), Piece::Type::WKing)));
		if (InBoard(x + 1, y + 1) && pieces[ToI(x + 1, y + 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y + 1), Piece::Type::WKing)));
		if (InBoard(x + 1, y + 0) && pieces[ToI(x + 1, y + 0)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y + 0), Piece::Type::WKing)));
		if (InBoard(x + 1, y - 1) && pieces[ToI(x + 1, y - 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y - 1), Piece::Type::WKing)));
		if (InBoard(x + 0, y - 1) && pieces[ToI(x + 0, y - 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 0, y - 1), Piece::Type::WKing)));
		if (InBoard(x - 1, y - 1) && pieces[ToI(x - 1, y - 1)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y - 1), Piece::Type::WKing)));
		if (InBoard(x - 1, y + 0) && pieces[ToI(x - 1, y + 0)].color() <= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y + 0), Piece::Type::WKing)));
	}
	else {
		if (InBoard(x - 1, y + 1) && pieces[ToI(x - 1, y + 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y + 1), Piece::Type::BKing)));
		if (InBoard(x + 0, y + 1) && pieces[ToI(x + 0, y + 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 0, y + 1), Piece::Type::BKing)));
		if (InBoard(x + 1, y + 1) && pieces[ToI(x + 1, y + 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y + 1), Piece::Type::BKing)));
		if (InBoard(x + 1, y + 0) && pieces[ToI(x + 1, y + 0)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y + 0), Piece::Type::BKing)));
		if (InBoard(x + 1, y - 1) && pieces[ToI(x + 1, y - 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 1, y - 1), Piece::Type::BKing)));
		if (InBoard(x + 0, y - 1) && pieces[ToI(x + 0, y - 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x + 0, y - 1), Piece::Type::BKing)));
		if (InBoard(x - 1, y - 1) && pieces[ToI(x - 1, y - 1)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y - 1), Piece::Type::BKing)));
		if (InBoard(x - 1, y + 0) && pieces[ToI(x - 1, y + 0)].color() >= 0) moves.push_back(Move(Square(pos, Piece::Type::None), Square(ToI(x - 1, y + 0), Piece::Type::BKing)));
	}
	return moves;
}

// Returns possible moves ofa piece
std::vector<Move> Board::getMoves(int pos) const {
	switch (pieces[pos].type) {
	case Piece::Type::WPawn:
	case Piece::Type::BPawn:
		return PawnMoves(pieces, pos);
		break;

	case Piece::Type::WKnight:
	case Piece::Type::BKnight:
		return KnightMoves(pieces, pos);
		break;

	case Piece::Type::WBishop:
	case Piece::Type::BBishop:
		return BishopMoves(pieces, pos);
		break;

	case Piece::Type::WRook:
	case Piece::Type::BRook:
		return RookMoves(pieces, pos);
		break;

	case Piece::Type::WQueen:
	case Piece::Type::BQueen:
		return QueenMoves(pieces, pos);
		break;

	case Piece::Type::WKing:
	case Piece::Type::BKing:
		return KingMoves(pieces, pos);
		break;

	default:
		return {};
	}
}
