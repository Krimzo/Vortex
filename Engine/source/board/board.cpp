#include "board/board.h"

#include "engine/engine.h"


static const kl::color board_colors[8]
{
	{ 240, 215, 180 },
	{ 180, 135, 100 },
	{ 180, 235, 240 },
	{ 100, 180, 175 },
	{ 205, 240, 175 },
	{ 145, 180, 95  },
	{ 240, 180, 175 },
	{ 170, 100, 90  },
};


board::board()
{}

void board::play_players_turn(const kl::window& window, const int clicked_index)
{
	if (position.get_win_state()) {
		return;
	}

	if (selected_square > -1) {
		std::vector<::position> positions = {};
		position.pieces[selected_square].get_moves(position, selected_square, positions);

		for (const auto& pos : positions) {
			if (clicked_index == pos.last_played_move.y) {
				this->position = pos;

				if (pos.get_win_state() > 0) {
					window.set_title("Player wins!");
				}
				else {
					play_engines_turn(window);
				}

				break;
			}
		}

		selected_square = -1;
	}
	else if (position.pieces[clicked_index].is_white()) {
		selected_square = clicked_index;
	}
}

void board::play_engines_turn(const kl::window& window)
{
	if (position.get_win_state()) {
		return;
	}

	window.set_title("Calculating..");

	engine engine = {};
	position = engine.find_best_position(this->position, 5);

	kl::print(std::fixed,
		"Search Depth: ", engine.get_search_depth(),
		" | Time: ", engine.get_search_time(),
		" | Calls: ", engine.get_call_count(),
		" | Eval: ", position.evaluation);

	window.set_title((position.get_win_state() < 0) ? "Engine wins!" : "Player's move");
}

static void draw_square(kl::image& target, const int index, const kl::color& light_color, const kl::color& dark_color)
{
	const int square_size = static_cast<int>(target.width()) / 8;
	const kl::int2 position = { index % 8, index / 8 };
	target.draw_rectangle(position * square_size, (position + kl::int2(1)) * square_size - kl::int2(1),
		((position.x % 2) == (position.y % 2)) ? light_color : dark_color, true);
}

void board::render(kl::image& target) const
{
	for (int i = 0; i < 64; i++) {
		if (i == selected_square) {
			draw_square(target, i, board_colors[2], board_colors[3]);
		}
		else {
			draw_square(target, i, board_colors[0], board_colors[1]);
		}
	}

	if (position.last_played_move.x >= 0 && position.last_played_move.y >= 0) {
		draw_square(target, position.last_played_move.x, board_colors[4], board_colors[5]);
		draw_square(target, position.last_played_move.y, board_colors[4], board_colors[5]);
	}

	if (selected_square >= 0) {
		std::vector<::position> positions;
		position.pieces[selected_square].get_moves(position, selected_square, positions);

		for (const auto& pos : positions) {
			draw_square(target, pos.last_played_move.y, board_colors[2], board_colors[3]);
		}
	}

	if (position.get_win_state()) {
		draw_square(target, position.last_played_move.y, board_colors[6], board_colors[7]);
	}

	for (int i = 0; i < 64; i++) {
		if (const kl::image* icon = position.pieces[i].get_icon()) {
			target.draw_image(kl::int2(i % 8, i / 8) * static_cast<int>(target.width() / 8), *icon);
		}
	}
}
