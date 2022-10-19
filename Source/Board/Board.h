#pragma once

#include "Position/Position.h"


class Board {
public:
	int selectedSquare = -1;
	Position position = {};

	Board();

	void playPlayersTurn(kl::Window& window, int clickedIndex);

	void playEnginesTurn(kl::Window& window);

	void render(kl::Image& target) const;
};
