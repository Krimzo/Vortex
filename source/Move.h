#pragma once

#include "Square.h"


class Move {
public:
	Square from;
	Square to;

	Move();
	Move(Square from, Square to);
};
