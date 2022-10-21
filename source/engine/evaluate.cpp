#include "engine/engine.h"


// Value tables
// Pawns
static constexpr float white_pawn_value_table[64]
{
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
	0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
	0.10f, 0.10f, 0.20f, 0.30f, 0.30f, 0.20f, 0.10f, 0.10f,
	0.05f, 0.05f, 0.10f, 0.25f, 0.25f, 0.10f, 0.05f, 0.05f,
	0.00f, 0.00f, 0.00f, 0.20f, 0.20f, 0.00f, 0.00f, 0.00f,
	0.05f, -0.05f, -0.10f, 0.00f, 0.00f, -0.10f, -0.05f, 0.05f,
	0.05f, 0.10f, 0.10f, -0.20f, -0.20f, 0.10f, 0.10f, 0.05f,
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
};
static constexpr float black_pawn_value_table[64]
{
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
	0.05f, 0.10f, 0.10f, -0.20f, -0.20f, 0.10f, 0.10f, 0.05f,
	0.05f, -0.05f, -0.10f, 0.00f, 0.00f, -0.10f, -0.05f, 0.05f,
	0.00f, 0.00f, 0.00f, 0.20f, 0.20f, 0.00f, 0.00f, 0.00f,
	0.05f, 0.05f, 0.10f, 0.25f, 0.25f, 0.10f, 0.05f, 0.05f,
	0.10f, 0.10f, 0.20f, 0.30f, 0.30f, 0.20f, 0.10f, 0.10f,
	0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
};

// Knights
static constexpr float white_knight_value_table[64]
{
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
	-0.40f, -0.20f, 0.00f, 0.00f, 0.00f, 0.00f, -0.20f, -0.40f,
	-0.30f, 0.00f, 0.10f, 0.15f, 0.15f, 0.10f, 0.00f, -0.30f,
	-0.30f, 0.05f, 0.15f, 0.20f, 0.20f, 0.15f, 0.05f, -0.30f,
	-0.30f, 0.00f, 0.15f, 0.20f, 0.20f, 0.15f, 0.00f, -0.30f,
	-0.30f, 0.05f, 0.10f, 0.15f, 0.15f, 0.10f, 0.05f, -0.30f,
	-0.40f, -0.20f, 0.00f, 0.05f, 0.05f, 0.00f, -0.20f, -0.40f,
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
};
static constexpr float black_knight_value_table[64]
{
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
	-0.40f, -0.20f, 0.00f, 0.05f, 0.05f, 0.00f, -0.20f, -0.40f,
	-0.30f, 0.05f, 0.10f, 0.15f, 0.15f, 0.10f, 0.05f, -0.30f,
	-0.30f, 0.00f, 0.15f, 0.20f, 0.20f, 0.15f, 0.00f, -0.30f,
	-0.30f, 0.05f, 0.15f, 0.20f, 0.20f, 0.15f, 0.05f, -0.30f,
	-0.30f, 0.00f, 0.10f, 0.15f, 0.15f, 0.10f, 0.00f, -0.30f,
	-0.40f, -0.20f, 0.00f, 0.00f, 0.00f, 0.00f, -0.20f, -0.40f,
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
};

// Bishops
static constexpr float white_bishop_value_table[64]
{
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
	-0.10f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.05f, 0.10f, 0.10f, 0.05f, 0.00f, -0.10f,
	-0.10f, 0.05f, 0.05f, 0.10f, 0.10f, 0.05f, 0.05f, -0.10f,
	-0.10f, 0.00f, 0.10f, 0.10f, 0.10f, 0.10f, 0.00f, -0.10f,
	-0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, -0.10f,
	-0.10f, 0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.05f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
};
static constexpr float black_bishop_value_table[64]
{
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
	-0.10f, 0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.05f, -0.10f,
	-0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, -0.10f,
	-0.10f, 0.00f, 0.10f, 0.10f, 0.10f, 0.10f, 0.00f, -0.10f,
	-0.10f, 0.05f, 0.05f, 0.10f, 0.10f, 0.05f, 0.05f, -0.10f,
	-0.10f, 0.00f, 0.05f, 0.10f, 0.10f, 0.05f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
};

// Rooks
static constexpr float white_rook_value_table[64]
{
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
	0.05f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	0.00f, 0.00f, 0.00f, 0.05f, 0.05f, 0.00f, 0.00f, 0.00f,
};
static constexpr float black_rook_value_table[64]
{
	0.00f, 0.00f, 0.00f, 0.05f, 0.05f, 0.00f, 0.00f, 0.00f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	0.05f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.05f,
	0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
};

// Queens											
static constexpr float white_queen_value_table[64]
{
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
	-0.10f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.10f,
	-0.05f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.05f,
	0.00f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.05f,
	-0.10f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.05f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
};
static constexpr float black_queen_value_table[64]
{
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
	-0.10f, 0.00f, 0.05f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.10f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.10f,
	0.00f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.05f,
	-0.10f, 0.00f, 0.05f, 0.05f, 0.05f, 0.05f, 0.00f, -0.10f,
	-0.10f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
};

// Kings											
static constexpr float white_king_mid_value_table[64]
{
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.20f, -0.30f, -0.30f, -0.40f, -0.40f, -0.30f, -0.30f, -0.20f,
	-0.10f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.10f,
	0.20f, 0.20f, 0.00f, 0.00f, 0.00f, 0.00f, 0.20f, 0.20f,
	0.20f, 0.30f, 0.10f, 0.00f, 0.00f, 0.10f, 0.30f, 0.20f,
};
static constexpr float black_king_mid_value_table[64]
{
	0.20f, 0.30f, 0.10f, 0.00f, 0.00f, 0.10f, 0.30f, 0.20f,
	0.20f, 0.20f, 0.00f, 0.00f, 0.00f, 0.00f, 0.20f, 0.20f,
	-0.10f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.20f, -0.10f,
	-0.20f, -0.30f, -0.30f, -0.40f, -0.40f, -0.30f, -0.30f, -0.20f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
	-0.30f, -0.40f, -0.40f, -0.50f, -0.50f, -0.40f, -0.40f, -0.30f,
};
static constexpr float white_king_end_value_table[64]
{
	-0.50f, -0.40f, -0.30f, -0.20f, -0.20f, -0.30f, -0.40f, -0.50f,
	-0.30f, -0.20f, -0.10f, 0.00f, 0.00f, -0.10f, -0.20f, -0.30f,
	-0.30f, -0.10f, 0.20f, 0.30f, 0.30f, 0.20f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.30f, 0.40f, 0.40f, 0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.30f, 0.40f, 0.40f, 0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.20f, 0.30f, 0.30f, 0.20f, -0.10f, -0.30f,
	-0.30f, -0.30f, 0.00f, 0.00f, 0.00f, 0.00f, -0.30f, -0.30f,
	-0.50f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.50f,
};
static constexpr float black_king_end_value_table[64]
{
	-0.50f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.30f, -0.50f,
	-0.30f, -0.30f, 0.00f, 0.00f, 0.00f, 0.00f, -0.30f, -0.30f,
	-0.30f, -0.10f, 0.20f, 0.30f, 0.30f, 0.20f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.30f, 0.40f, 0.40f, 0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.30f, 0.40f, 0.40f, 0.30f, -0.10f, -0.30f,
	-0.30f, -0.10f, 0.20f, 0.30f, 0.30f, 0.20f, -0.10f, -0.30f,
	-0.30f, -0.20f, -0.10f, 0.00f, 0.00f, -0.10f, -0.20f, -0.30f,
	-0.50f, -0.40f, -0.30f, -0.20f, -0.20f, -0.30f, -0.40f, -0.50f,
};


static bool white_in_endgame(const position& position)
{
	int minor_pieces = 0;
	for (const auto piece : position.pieces) {
		switch (piece.type) {
		case b_queen:
			return false;

		case b_knight:
		case b_bishop:
		case b_rook:
			if (++minor_pieces > 2) {
				return false;
			}
		}
	}
	return true;
}

static bool black_in_endgame(const position& position)
{
	int minor_pieces = 0;
	for (const auto piece : position.pieces) {
		switch (piece.type) {
		case w_queen:
			return false;

		case w_knight:
		case w_bishop:
		case w_rook:
			if (++minor_pieces > 2) {
				return false;
			}
		}
	}
	return true;
}

float engine::static_evaluation(const position& position)
{
	float eval = 0.0f;
	for (int i = 0; i < 64; i++) {
		switch (position.pieces[i].type) {
		case w_pawn:
			eval += 1.0f;
			eval += white_pawn_value_table[i];
			break;
		case w_knight:
			eval += 3.2f;
			eval += white_knight_value_table[i];
			break;
		case w_bishop:
			eval += 3.3f;
			eval += white_bishop_value_table[i];
			break;
		case w_rook:
			eval += 5.0f;
			eval += white_rook_value_table[i];
			break;
		case w_queen:
			eval += 9.0f;
			eval += white_queen_value_table[i];
			break;
		case w_king:
			eval += 1'000'000.0f;
			eval += white_in_endgame(position) ? white_king_end_value_table[i] : white_king_mid_value_table[i];
			break;

		case b_pawn:
			eval -= 1.0f;
			eval -= black_pawn_value_table[i];
			break;
		case b_knight:
			eval -= 3.2f;
			eval -= black_knight_value_table[i];
			break;
		case b_bishop:
			eval -= 3.3f;
			eval -= black_bishop_value_table[i];
			break;
		case b_rook:
			eval -= 5.0f;
			eval -= black_rook_value_table[i];
			break;
		case b_queen:
			eval -= 9.0f;
			eval -= black_queen_value_table[i];
			break;
		case b_king:
			eval -= 1'000'000.0f;
			eval -= black_in_endgame(position) ? black_king_end_value_table[i] : black_king_mid_value_table[i];
			break;
		}
	}
	return eval;
}
