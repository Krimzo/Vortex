#include "piece/piece.h"

#include "position/position.h"


static void get_white_king_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	if (in_board(x - 1, y + 1) && position.pieces[get_index(x - 1, y + 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y + 1), w_king));
	if (in_board(x + 0, y + 1) && position.pieces[get_index(x + 0, y + 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 0, y + 1), w_king));
	if (in_board(x + 1, y + 1) && position.pieces[get_index(x + 1, y + 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y + 1), w_king));
	if (in_board(x + 1, y + 0) && position.pieces[get_index(x + 1, y + 0)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y + 0), w_king));
	if (in_board(x + 1, y - 1) && position.pieces[get_index(x + 1, y - 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y - 1), w_king));
	if (in_board(x + 0, y - 1) && position.pieces[get_index(x + 0, y - 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 0, y - 1), w_king));
	if (in_board(x - 1, y - 1) && position.pieces[get_index(x - 1, y - 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y - 1), w_king));
	if (in_board(x - 1, y + 0) && position.pieces[get_index(x - 1, y + 0)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y + 0), w_king));

	if (position.castling_wk && !position.pieces[61].exists() && !position.pieces[62].exists()) {
		::position new_position = position.after_playing(60, 62, w_king);
		new_position.pieces[63].type = none;
		new_position.pieces[61].type = w_rook;
		out_positions.push_back(new_position);
	}
	if (position.castling_wq && !position.pieces[57].exists() && !position.pieces[58].exists() && !position.pieces[59].exists()) {
		::position new_position = position.after_playing(60, 58, w_king);
		new_position.pieces[56].type = none;
		new_position.pieces[59].type = w_rook;
		out_positions.push_back(new_position);
	}
}

static void get_black_king_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	if (in_board(x - 1, y + 1) && position.pieces[get_index(x - 1, y + 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y + 1), b_king));
	if (in_board(x + 0, y + 1) && position.pieces[get_index(x + 0, y + 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 0, y + 1), b_king));
	if (in_board(x + 1, y + 1) && position.pieces[get_index(x + 1, y + 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y + 1), b_king));
	if (in_board(x + 1, y + 0) && position.pieces[get_index(x + 1, y + 0)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y + 0), b_king));
	if (in_board(x + 1, y - 1) && position.pieces[get_index(x + 1, y - 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y - 1), b_king));
	if (in_board(x + 0, y - 1) && position.pieces[get_index(x + 0, y - 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 0, y - 1), b_king));
	if (in_board(x - 1, y - 1) && position.pieces[get_index(x - 1, y - 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y - 1), b_king));
	if (in_board(x - 1, y + 0) && position.pieces[get_index(x - 1, y + 0)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y + 0), b_king));

	if (position.castling_bk && !position.pieces[5].exists() && !position.pieces[6].exists()) {
		::position new_position = position.after_playing(4, 6, b_king);
		new_position.pieces[7].type = none;
		new_position.pieces[5].type = b_rook;
		out_positions.push_back(new_position);
	}
	if (position.castling_bq && !position.pieces[1].exists() && !position.pieces[2].exists() && !position.pieces[3].exists()) {
		::position new_position = position.after_playing(4, 2, b_king);
		new_position.pieces[0].type = none;
		new_position.pieces[3].type = b_rook;
		out_positions.push_back(new_position);
	}
}

void piece::get_king_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions) const
{
	if (this->is_white()) {
		get_white_king_moves(position, x, y, out_positions);
	}
	else {
		get_black_king_moves(position, x, y, out_positions);
	}
}
