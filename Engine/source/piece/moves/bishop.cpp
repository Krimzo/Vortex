#include "piece/piece.h"

#include "position/position.h"


static void get_white_bishop_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y + i);
		if (in_board(x + i, y + i)) {
			if (!position.pieces[index].exists()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, w_bishop));
			}
			else if (position.pieces[index].is_black()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, w_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y + i);
		if (in_board(x - i, y + i)) {
			if (!position.pieces[index].exists()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, w_bishop));
			}
			else if (position.pieces[index].is_black()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, w_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y - i);
		if (in_board(x + i, y - i)) {
			if (!position.pieces[index].exists()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, w_bishop));
			}
			else if (position.pieces[index].is_black()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, w_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y - i);
		if (in_board(x - i, y - i)) {
			if (!position.pieces[index].exists()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, w_bishop));
			}
			else if (position.pieces[index].is_black()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, w_bishop));
				break;
			}
			else {
				break;
			}
		}
	}
}

static void get_black_bishop_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions)
{
	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y + i);
		if (in_board(x + i, y + i)) {
			if (!position.pieces[index].exists()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, b_bishop));
			}
			else if (position.pieces[index].is_black()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, b_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y + i);
		if (in_board(x - i, y + i)) {
			if (!position.pieces[index].exists()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, b_bishop));
			}
			else if (position.pieces[index].is_black()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, b_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x + i, y - i);
		if (in_board(x + i, y - i)) {
			if (!position.pieces[index].exists()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, b_bishop));
			}
			else if (position.pieces[index].is_black()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, b_bishop));
				break;
			}
			else {
				break;
			}
		}
	}

	for (int i = 1; i < 8; i++) {
		const int index = get_index(x - i, y - i);
		if (in_board(x - i, y - i)) {
			if (!position.pieces[index].exists()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, b_bishop));
			}
			else if (position.pieces[index].is_black()) {
				out_positions.push_back(position.after_playing(get_index(x, y), index, b_bishop));
				break;
			}
			else {
				break;
			}
		}
	}
}

void piece::get_bishop_moves(const position& position, const int x, const int y, std::vector<::position>& out_positions) const
{
	if (this->is_white()) {
		get_white_bishop_moves(position, x, y, out_positions);
	}
	else {
		get_black_bishop_moves(position, x, y, out_positions);
	}
}
