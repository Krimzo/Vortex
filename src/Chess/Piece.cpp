#include "Chess/Piece.h"


// Returns piece type
int PieceColor(Piece piece) {
	switch (piece) {
	case Piece::WPawn:
		return 1;
	case Piece::WKnight:
		return 1;
	case Piece::WBishop:
		return 1;
	case Piece::WRook:
		return 1;
	case Piece::WQueen:
		return 1;
	case Piece::WKing:
		return 1;

	case Piece::BPawn:
		return -1;
	case Piece::BKnight:
		return -1;
	case Piece::BBishop:
		return -1;
	case Piece::BRook:
		return -1;
	case Piece::BQueen:
		return -1;
	case Piece::BKing:
		return -1;

	default:
		return 0;
	}
}

// Special piece type moves
std::vector<int> PawnMoves(const std::vector<Piece>& pieces, int pos);
std::vector<int> KnightMoves(const std::vector<Piece>& pieces, int pos);
std::vector<int> BishopMoves(const std::vector<Piece>& pieces, int pos);
std::vector<int> RookMoves(const std::vector<Piece>& pieces, int pos);
std::vector<int> QueenMoves(const std::vector<Piece>& pieces, int pos);
std::vector<int> KingMoves(const std::vector<Piece>& pieces, int pos);

// Returns possible moves
std::vector<int> PieceMoves(const std::vector<Piece>& pieces, int pos) {
	switch (pieces[pos]) {
	case Piece::WPawn:
	case Piece::BPawn:
		return PawnMoves(pieces, pos);
		break;

	case Piece::WKnight:
	case Piece::BKnight:
		return KnightMoves(pieces, pos);
		break;

	case Piece::WBishop:
	case Piece::BBishop:
		return BishopMoves(pieces, pos);
		break;

	case Piece::WRook:
	case Piece::BRook:
		return RookMoves(pieces, pos);
		break;

	case Piece::WQueen:
	case Piece::BQueen:
		return QueenMoves(pieces, pos);
		break;

	case Piece::WKing:
	case Piece::BKing:
		return KingMoves(pieces, pos);
		break;

	default:
		return {};
	}
}

// XY to I
size_t ToI(int x, int y) {
	return size_t(y * 8 + x);
}
bool InBoard(int x, int y) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8) {
		return true;
	}
	return false;
}

// Special piece type moves
std::vector<int> PawnMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<int> moves;
	if (PieceColor(pieces[pos]) > 0) {
		// Moving
		if (InBoard(x, y - 1) && PieceColor(pieces[ToI(x, y - 1)]) == 0) {
			// Highlighting 1 y up
			moves.push_back(ToI(x, y - 1));

			// Highlighting 2 y up
			if (y == 6 && PieceColor(pieces[ToI(x, y - 2)]) == 0) {
				moves.push_back(ToI(x, y - 2));
			}
		}

		// Eating
		// Left
		if (InBoard(x - 1, y - 1) && PieceColor(pieces[ToI(x - 1, y - 1)]) < 0) {
			moves.push_back(ToI(x - 1, y - 1));
		}
		// Right
		if (InBoard(x + 1, y - 1) && PieceColor(pieces[ToI(x + 1, y - 1)]) < 0) {
			moves.push_back(ToI(x + 1, y - 1));
		}
	}
	else {
		// Moving
		if (InBoard(x, y + 1) && PieceColor(pieces[ToI(x, y + 1)]) == 0) {
			// Highlighting 1 y up
			moves.push_back(ToI(x, y + 1));

			// Highlighting 2 y up
			if (y == 1 && PieceColor(pieces[ToI(x, y + 2)]) == 0) {
				moves.push_back(ToI(x, y + 2));
			}
		}

		// Eating
		// Left
		if (InBoard(x - 1, y + 1) && PieceColor(pieces[ToI(x - 1, y + 1)]) > 0) {
			moves.push_back(ToI(x - 1, y + 1));
		}
		// Right
		if (InBoard(x + 1, y + 1) && PieceColor(pieces[ToI(x + 1, y + 1)]) > 0) {
			moves.push_back(ToI(x + 1, y + 1));
		}
	}
	return moves;
}
std::vector<int> KnightMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<int> moves;
	if (PieceColor(pieces[pos]) > 0) {
		if (InBoard(x + 1, y + 2) && PieceColor(pieces[ToI(x + 1, y + 2)]) <= 0) moves.push_back(ToI(x + 1, y + 2));
		if (InBoard(x - 1, y + 2) && PieceColor(pieces[ToI(x - 1, y + 2)]) <= 0) moves.push_back(ToI(x - 1, y + 2));
		if (InBoard(x + 1, y - 2) && PieceColor(pieces[ToI(x + 1, y - 2)]) <= 0) moves.push_back(ToI(x + 1, y - 2));
		if (InBoard(x - 1, y - 2) && PieceColor(pieces[ToI(x - 1, y - 2)]) <= 0) moves.push_back(ToI(x - 1, y - 2));
		if (InBoard(x + 2, y + 1) && PieceColor(pieces[ToI(x + 2, y + 1)]) <= 0) moves.push_back(ToI(x + 2, y + 1));
		if (InBoard(x + 2, y - 1) && PieceColor(pieces[ToI(x + 2, y - 1)]) <= 0) moves.push_back(ToI(x + 2, y - 1));
		if (InBoard(x - 2, y + 1) && PieceColor(pieces[ToI(x - 2, y + 1)]) <= 0) moves.push_back(ToI(x - 2, y + 1));
		if (InBoard(x - 2, y - 1) && PieceColor(pieces[ToI(x - 2, y - 1)]) <= 0) moves.push_back(ToI(x - 2, y - 1));
	}
	else {
		if (InBoard(x + 1, y + 2) && PieceColor(pieces[ToI(x + 1, y + 2)]) >= 0) moves.push_back(ToI(x + 1, y + 2));
		if (InBoard(x - 1, y + 2) && PieceColor(pieces[ToI(x - 1, y + 2)]) >= 0) moves.push_back(ToI(x - 1, y + 2));
		if (InBoard(x + 1, y - 2) && PieceColor(pieces[ToI(x + 1, y - 2)]) >= 0) moves.push_back(ToI(x + 1, y - 2));
		if (InBoard(x - 1, y - 2) && PieceColor(pieces[ToI(x - 1, y - 2)]) >= 0) moves.push_back(ToI(x - 1, y - 2));
		if (InBoard(x + 2, y + 1) && PieceColor(pieces[ToI(x + 2, y + 1)]) >= 0) moves.push_back(ToI(x + 2, y + 1));
		if (InBoard(x + 2, y - 1) && PieceColor(pieces[ToI(x + 2, y - 1)]) >= 0) moves.push_back(ToI(x + 2, y - 1));
		if (InBoard(x - 2, y + 1) && PieceColor(pieces[ToI(x - 2, y + 1)]) >= 0) moves.push_back(ToI(x - 2, y + 1));
		if (InBoard(x - 2, y - 1) && PieceColor(pieces[ToI(x - 2, y - 1)]) >= 0) moves.push_back(ToI(x - 2, y - 1));
	}
	return moves;
}
std::vector<int> BishopMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<int> moves;
	if (PieceColor(pieces[pos]) > 0) {
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x + i, y + i);
			if (InBoard(x + i, y + i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) < 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x - i, y + i);
			if (InBoard(x - i, y + i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) < 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x + i, y - i);
			if (InBoard(x + i, y - i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) < 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x - i, y - i);
			if (InBoard(x - i, y - i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) < 0) {
					moves.push_back(ind);
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
			const size_t ind = ToI(x + i, y + i);
			if (InBoard(x + i, y + i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) > 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x - i, y + i);
			if (InBoard(x - i, y + i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) > 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x + i, y - i);
			if (InBoard(x + i, y - i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) > 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x - i, y - i);
			if (InBoard(x - i, y - i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) > 0) {
					moves.push_back(ind);
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
std::vector<int> RookMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<int> moves;
	if (PieceColor(pieces[pos]) > 0) {
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x + i, y);
			if (InBoard(x + i, y)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) < 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x - i, y);
			if (InBoard(x - i, y)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) < 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x, y + i);
			if (InBoard(x, y + i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) < 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x, y - i);
			if (InBoard(x, y - i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) < 0) {
					moves.push_back(ind);
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
			const size_t ind = ToI(x + i, y);
			if (InBoard(x + i, y)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) > 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x - i, y);
			if (InBoard(x - i, y)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) > 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x, y + i);
			if (InBoard(x, y + i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) > 0) {
					moves.push_back(ind);
					break;
				}
				else {
					break;
				}
			}
		}
		for (int i = 1; i < 8; i++) {
			const size_t ind = ToI(x, y - i);
			if (InBoard(x, y - i)) {
				if (PieceColor(pieces[ind]) == 0) {
					moves.push_back(ind);
				}
				else if (PieceColor(pieces[ind]) > 0) {
					moves.push_back(ind);
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
std::vector<int> QueenMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<int> moves = BishopMoves(pieces, pos);
	const std::vector<int> rookMoves = RookMoves(pieces, pos);
	for (int rm : rookMoves) moves.push_back(rm);
	return moves;
}
std::vector<int> KingMoves(const std::vector<Piece>& pieces, int pos) {
	const int x = pos % 8;
	const int y = pos / 8;

	std::vector<int> moves;
	if (PieceColor(pieces[pos]) > 0) {
		if (InBoard(x - 1, y + 1) && PieceColor(pieces[ToI(x - 1, y + 1)]) <= 0) moves.push_back(ToI(x - 1, y + 1));
		if (InBoard(x + 0, y + 1) && PieceColor(pieces[ToI(x + 0, y + 1)]) <= 0) moves.push_back(ToI(x + 0, y + 1));
		if (InBoard(x + 1, y + 1) && PieceColor(pieces[ToI(x + 1, y + 1)]) <= 0) moves.push_back(ToI(x + 1, y + 1));
		if (InBoard(x + 1, y + 0) && PieceColor(pieces[ToI(x + 1, y + 0)]) <= 0) moves.push_back(ToI(x + 1, y + 0));
		if (InBoard(x + 1, y - 1) && PieceColor(pieces[ToI(x + 1, y - 1)]) <= 0) moves.push_back(ToI(x + 1, y - 1));
		if (InBoard(x + 0, y - 1) && PieceColor(pieces[ToI(x + 0, y - 1)]) <= 0) moves.push_back(ToI(x + 0, y - 1));
		if (InBoard(x - 1, y - 1) && PieceColor(pieces[ToI(x - 1, y - 1)]) <= 0) moves.push_back(ToI(x - 1, y - 1));
		if (InBoard(x - 1, y + 0) && PieceColor(pieces[ToI(x - 1, y + 0)]) <= 0) moves.push_back(ToI(x - 1, y + 0));
	}
	else {
		if (InBoard(x - 1, y + 1) && PieceColor(pieces[ToI(x - 1, y + 1)]) >= 0) moves.push_back(ToI(x - 1, y + 1));
		if (InBoard(x + 0, y + 1) && PieceColor(pieces[ToI(x + 0, y + 1)]) >= 0) moves.push_back(ToI(x + 0, y + 1));
		if (InBoard(x + 1, y + 1) && PieceColor(pieces[ToI(x + 1, y + 1)]) >= 0) moves.push_back(ToI(x + 1, y + 1));
		if (InBoard(x + 1, y + 0) && PieceColor(pieces[ToI(x + 1, y + 0)]) >= 0) moves.push_back(ToI(x + 1, y + 0));
		if (InBoard(x + 1, y - 1) && PieceColor(pieces[ToI(x + 1, y - 1)]) >= 0) moves.push_back(ToI(x + 1, y - 1));
		if (InBoard(x + 0, y - 1) && PieceColor(pieces[ToI(x + 0, y - 1)]) >= 0) moves.push_back(ToI(x + 0, y - 1));
		if (InBoard(x - 1, y - 1) && PieceColor(pieces[ToI(x - 1, y - 1)]) >= 0) moves.push_back(ToI(x - 1, y - 1));
		if (InBoard(x - 1, y + 0) && PieceColor(pieces[ToI(x - 1, y + 0)]) >= 0) moves.push_back(ToI(x - 1, y + 0));
	}
	return moves;
}
