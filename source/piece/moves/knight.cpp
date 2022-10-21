#include "piece/piece.h"

#include "position/position.h"


static void get_white_knight_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	if (in_board(x + 1, y + 2) && position.pieces[get_index(x + 1, y + 2)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y + 2), w_knight));
	if (in_board(x - 1, y + 2) && position.pieces[get_index(x - 1, y + 2)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y + 2), w_knight));
	if (in_board(x + 1, y - 2) && position.pieces[get_index(x + 1, y - 2)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y - 2), w_knight));
	if (in_board(x - 1, y - 2) && position.pieces[get_index(x - 1, y - 2)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y - 2), w_knight));
	if (in_board(x + 2, y + 1) && position.pieces[get_index(x + 2, y + 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 2, y + 1), w_knight));
	if (in_board(x + 2, y - 1) && position.pieces[get_index(x + 2, y - 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 2, y - 1), w_knight));
	if (in_board(x - 2, y + 1) && position.pieces[get_index(x - 2, y + 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 2, y + 1), w_knight));
	if (in_board(x - 2, y - 1) && position.pieces[get_index(x - 2, y - 1)].is_black(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 2, y - 1), w_knight));
}

static void get_black_knight_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	if (in_board(x + 1, y + 2) && position.pieces[get_index(x + 1, y + 2)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y + 2), b_knight));
	if (in_board(x - 1, y + 2) && position.pieces[get_index(x - 1, y + 2)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y + 2), b_knight));
	if (in_board(x + 1, y - 2) && position.pieces[get_index(x + 1, y - 2)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 1, y - 2), b_knight));
	if (in_board(x - 1, y - 2) && position.pieces[get_index(x - 1, y - 2)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 1, y - 2), b_knight));
	if (in_board(x + 2, y + 1) && position.pieces[get_index(x + 2, y + 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 2, y + 1), b_knight));
	if (in_board(x + 2, y - 1) && position.pieces[get_index(x + 2, y - 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x + 2, y - 1), b_knight));
	if (in_board(x - 2, y + 1) && position.pieces[get_index(x - 2, y + 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 2, y + 1), b_knight));
	if (in_board(x - 2, y - 1) && position.pieces[get_index(x - 2, y - 1)].is_white(true)) out_positions.push_back(position.after_playing(get_index(x, y), get_index(x - 2, y - 1), b_knight));
}

void piece::get_knight_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions) const
{
	if (this->is_white()) {
		get_white_knight_moves(position, x, y, out_positions);
	}
	else {
		get_black_knight_moves(position, x, y, out_positions);
	}
}
