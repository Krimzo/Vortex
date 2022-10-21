#include "piece/piece.h"

#include "position/position.h"


static void get_white_pawn_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	if (in_board(x, y - 1) && !position.pieces[get_index(x, y - 1)].exists()) {
		out_positions.push_back(position.after_playing(get_index(x, y), get_index(x, y - 1), (y == 1) ? w_queen : w_pawn));

		if (y == 6 && !position.pieces[get_index(x, y - 2)].exists()) {
			out_positions.push_back(position.after_playing(get_index(x, y), get_index(x, y - 2), w_pawn));
		}
	}

	if (in_board(x - 1, y - 1) && position.pieces[get_index(x - 1, y - 1)].is_black()) {
		out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y - 1), (y == 1) ? w_queen : w_pawn));
	}
	if (in_board(x + 1, y - 1) && position.pieces[get_index(x + 1, y - 1)].is_black()) {
		out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y - 1), (y == 1) ? w_queen : w_pawn));
	}
}

static void get_black_pawn_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	if (in_board(x, y + 1) && !position.pieces[get_index(x, y + 1)].exists()) {
		out_positions.push_back(position.after_playing(get_index(x, y), get_index(x, y + 1), (y == 6) ? b_queen : b_pawn));

		if (y == 1 && !position.pieces[get_index(x, y + 2)].exists()) {
			out_positions.push_back(position.after_playing(get_index(x, y), get_index(x, y + 2), b_pawn));
		}
	}

	if (in_board(x - 1, y + 1) && position.pieces[get_index(x - 1, y + 1)].is_white()) {
		out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y + 1), (y == 6) ? b_queen : b_pawn));
	}
	if (in_board(x + 1, y + 1) && position.pieces[get_index(x + 1, y + 1)].is_white()) {
		out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y + 1), (y == 6) ? b_queen : b_pawn));
	}
}

void piece::get_pawn_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions) const
{
	if (this->is_white()) {
		get_white_pawn_moves(position, x, y, out_positions);
	}
	else {
		get_black_pawn_moves(position, x, y, out_positions);
	}
}
