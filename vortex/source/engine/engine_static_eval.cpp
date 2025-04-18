#include "vortex.h"


static constexpr int32_t piece_value_table[vtx::_PIECE_TYPE_COUNT] = {
	 0,
	 100,  320,  330,  500,  900,  1'000'000,
    -100, -320, -330, -500, -900, -1'000'000,
};

static constexpr int8_t piece_position_table[vtx::_PIECE_TYPE_COUNT][8 * 8] = {
	{ // none
	},
	{ // white pawn
		00,  00,  00,  00,  00,  00,  00, 00,
		50,  50,  50,  50,  50,  50,  50, 50,
		10,  10,  20,  30,  30,  20,  10, 10,
		05,  05,  10,  25,  25,  10,  05, 05,
		00,  00,  00,  20,  20,  00,  00, 00,
		05, -05, -10,  00,  00, -10, -05, 05,
		05,  10,  10, -20, -20,  10,  10, 05,
		00,  00,  00,  00,  00,  00,  00, 00,
	},
	{ // white knight
		-50, -40, -30, -30, -30, -30, -40, -50,
		-40, -20,  00,  00,  00,  00, -20, -40,
		-30,  00,  10,  15,  15,  10,  00, -30,
		-30,  05,  15,  20,  20,  15,  05, -30,
		-30,  00,  15,  20,  20,  15,  00, -30,
		-30,  05,  10,  15,  15,  10,  05, -30,
		-40, -20,  00,  05,  05,  00, -20, -40,
		-50, -40, -30, -30, -30, -30, -40, -50,
	},
	{ // white bishop
		-20, -10, -10, -10, -10, -10, -10, -20,
		-10,  00,  00,  00,  00,  00,  00, -10,
		-10,  00,  05,  10,  10,  05,  00, -10,
		-10,  05,  05,  10,  10,  05,  05, -10,
		-10,  00,  10,  10,  10,  10,  00, -10,
		-10,  10,  10,  10,  10,  10,  10, -10,
		-10,  05,  00,  00,  00,  00,  05, -10,
		-20, -10, -10, -10, -10, -10, -10, -20,
	},
	{ // white rook
		 00, 00, 00, 00, 00, 00, 00,  00,
		 05, 10, 10, 10, 10, 10, 10,  05,
		-05, 00, 00, 00, 00, 00, 00, -05,
		-05, 00, 00, 00, 00, 00, 00, -05,
		-05, 00, 00, 00, 00, 00, 00, -05,
		-05, 00, 00, 00, 00, 00, 00, -05,
		-05, 00, 00, 00, 00, 00, 00, -05,
		 00, 00, 00, 05, 05, 00, 00,  00,
	},
	{ // white queen
		-20, -10, -10, -05, -05, -10, -10, -20,
		-10,  00,  00,  00,  00,  00,  00, -10,
		-10,  00,  05,  05,  05,  05,  00, -10,
		-05,  00,  05,  05,  05,  05,  00, -05,
		 00,  00,  05,  05,  05,  05,  00, -05,
		-10,  05,  05,  05,  05,  05,  00, -10,
		-10,  00,  05,  00,  00,  00,  00, -10,
		-20, -10, -10, -05, -05, -10, -10, -20,
	},
	{ // white king
		-40, -40, -35, -35, -35, -35, -40, -40,
		-30, -30, -25, -25, -25, -25, -30, -30,
		-30, -25, -10, -10, -10, -10, -25, -30,
		-30, -25, -05, -05, -05, -05, -25, -30,
		-25, -20,  00,  00,  00,  00, -20, -25,
		-20, -15,  00,  05,  05,  00, -15, -20,
		-05, -05,  00,  00,  00,  00, -05, -05,
		-15,  00, -10, -15, -15, -10,  00, -15,
	},
	{ // black pawn
		 00,  00,  00,  00,  00,  00,  00,  00,
		-05, -10, -10,  20,  20, -10, -10, -05,
		-05,  05,  10,  00,  00,  10,  05, -05,
		 00,  00,  00, -20, -20,  00,  00,  00,
		-05, -05, -10, -25, -25, -10, -05, -05,
		-10, -10, -20, -30, -30, -20, -10, -10,
		-50, -50, -50, -50, -50, -50, -50, -50,
		 00,  00,  00,  00,  00,  00,  00,  00,
	},
	{ // black knight
		 50,  40,  30,  30,  30,  30,  40,  50,
		 40,  20,  00, -05, -05,  00,  20,  40,
		 30, -05, -10, -15, -15, -10, -05,  30,
		 30,  00, -15, -20, -20, -15,  00,  30,
		 30, -05, -15, -20, -20, -15, -05,  30,
		 30,  00, -10, -15, -15, -10,  00,  30,
		 40,  20,  00,  00,  00,  00,  20,  40,
		 50,  40,  30,  30,  30,  30,  40,  50,
	},
	{ // black bishop
		 20,  10,  10,  10,  10,  10,  10,  20,
		 10, -05,  00,  00,  00,  00, -05,  10,
		 10, -10, -10, -10, -10, -10, -10,  10,
		 10,  00, -10, -10, -10, -10,  00,  10,
		 10, -05, -05, -10, -10, -05, -05,  10,
		 10,  00, -05, -10, -10, -05,  00,  10,
		 10,  00,  00,  00,  00,  00,  00,  10,
		 20,  10,  10,  10,  10,  10,  10,  20,
	},
	{ // black rook
		 00,  00,  00, -05, -05,  00,  00,  00,
		 05,  00,  00,  00,  00,  00,  00,  05,
		 05,  00,  00,  00,  00,  00,  00,  05,
		 05,  00,  00,  00,  00,  00,  00,  05,
		 05,  00,  00,  00,  00,  00,  00,  05,
		 05,  00,  00,  00,  00,  00,  00,  05,
		-05, -10, -10, -10, -10, -10, -10, -05,
		 00,  00,  00,  00,  00,  00,  00,  00,
	},
	{ // black queen
		 20,  10,  10,  05,  05,  10,  10,  20,
		 10,  00, -05,  00,  00,  00,  00,  10,
		 10, -05, -05, -05, -05, -05,  00,  10,
		 00,  00, -05, -05, -05, -05,  00,  05,
		 05,  00, -05, -05, -05, -05,  00,  05,
		 10,  00, -05, -05, -05, -05,  00,  10,
		 10,  00,  00,  00,  00,  00,  00,  10,
		 20,  10,  10,  05,  05,  10,  10,  20,
	},
	{ // black king
		 15,  00,  10,  15,  15,  10,  00,  15,
		 05,  05,  00,  00,  00,  00,  05,  05,
		 20,  15,  00, -05, -05,  00,  15,  20,
		 25,  20,  00,  00,  00,  00,  20,  25,
		 30,  25,  05,  05,  05,  05,  25,  30,
		 30,  25,  10,  10,  10,  10,  25,  30,
		 30,  30,  25,  25,  25,  25,  30,  30,
		 40,  40,  35,  35,  35,  35,  40,  40,
	},
};

int64_t vtx::Engine::static_eval(Board const& board)
{
	int64_t evaluation = 0;
	for (int i = 0; i < 64; i++)
	{
		evaluation += piece_value_table[board.pieces[i].type];
		evaluation += piece_position_table[board.pieces[i].type][i];
	}
	return evaluation;
}
