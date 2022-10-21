#pragma once

#include "position/position.h"


class board
{
public:
	int selected_square = -1;
	position position = {};

	board();

	void play_players_turn(const kl::window& window, int clicked_index);

	void play_engines_turn(const kl::window& window);

	void render(kl::image& target) const;
};
