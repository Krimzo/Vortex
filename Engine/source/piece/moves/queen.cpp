#include "piece/piece.h"

#include "position/position.h"


static void get_white_queen_moves(const piece& piece, const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	std::vector<::position> bishop_positions = {};
	piece.get_bishop_moves(position, x, y, bishop_positions);

	for (auto& pos : bishop_positions) {
		pos.pieces[pos.last_played_move.y].type = w_queen;
		out_positions.push_back(pos);
	}

	std::vector<::position> rook_positions;
	piece.get_rook_moves(position, x, y, rook_positions);

	for (auto& pos : rook_positions) {
		pos.pieces[pos.last_played_move.y].type = w_queen;
		out_positions.push_back(pos);
	}
}

static void get_black_queen_moves(const piece& piece, const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	std::vector<::position> bishop_positions = {};
	piece.get_bishop_moves(position, x, y, bishop_positions);

	for (auto& pos : bishop_positions) {
		pos.pieces[pos.last_played_move.y].type = b_queen;
		out_positions.push_back(pos);
	}

	std::vector<::position> rook_positions;
	piece.get_rook_moves(position, x, y, rook_positions);

	for (auto& pos : rook_positions) {
		pos.pieces[pos.last_played_move.y].type = b_queen;
		out_positions.push_back(pos);
	}
}

void piece::get_queen_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions) const
{
	if (this->is_white()) {
		get_white_queen_moves(*this, position, x, y, out_positions);
	}
	else {
		get_black_queen_moves(*this, position, x, y, out_positions);
	}
}
