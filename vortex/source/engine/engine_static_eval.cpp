#include "vortex.h"


// Value tables
// Pawns
static constexpr float white_pawn_value_table[64]
{
	0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, 0.00f,
	0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f, 0.50f,
	0.10f,  0.10f,  0.20f,  0.30f,  0.30f,  0.20f,  0.10f, 0.10f,
	0.05f,  0.05f,  0.10f,  0.25f,  0.25f,  0.10f,  0.05f, 0.05f,
	0.00f,  0.00f,  0.00f,  0.20f,  0.20f,  0.00f,  0.00f, 0.00f,
	0.05f, -0.05f, -0.10f,  0.00f,  0.00f, -0.10f, -0.05f, 0.05f,
	0.05f,  0.10f,  0.10f, -0.20f, -0.20f,  0.10f,  0.10f, 0.05f,
	0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, 0.00f,
};
static constexpr float black_pawn_value_table[64]
{
	0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, 0.00f,
	0.05f,  0.10f,  0.10f, -0.20f, -0.20f,  0.10f,  0.10f, 0.05f,
	0.05f, -0.05f, -0.10f,  0.00f,  0.00f, -0.10f, -0.05f, 0.05f,
	0.00f,  0.00f,  0.00f,  0.20f,  0.20f,  0.00f,  0.00f, 0.00f,
	0.05f,  0.05f,  0.10f,  0.25f,  0.25f,  0.10f,  0.05f, 0.05f,
	0.10f,  0.10f,  0.20f,  0.30f,  0.30f,  0.20f,  0.10f, 0.10f,
	0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f,  0.50f, 0.50f,
	0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, 0.00f,
};

// Knights
static constexpr float white_knight_value_table[64]
{
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
	-0.40f, -0.20f,  0.00f,  0.00f,  0.00f,  0.00f, -0.20f, -0.40f,
	-0.30f,  0.00f,  0.10f,  0.15f,  0.15f,  0.10f,  0.00f, -0.30f,
	-0.30f,  0.05f,  0.15f,  0.20f,  0.20f,  0.15f,  0.05f, -0.30f,
	-0.30f,  0.00f,  0.15f,  0.20f,  0.20f,  0.15f,  0.00f, -0.30f,
	-0.30f,  0.05f,  0.10f,  0.15f,  0.15f,  0.10f,  0.05f, -0.30f,
	-0.40f, -0.20f,  0.00f,  0.05f,  0.05f,  0.00f, -0.20f, -0.40f,
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
};
static constexpr float black_knight_value_table[64]
{
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
	-0.40f, -0.20f,  0.00f,  0.05f,  0.05f,  0.00f, -0.20f, -0.40f,
	-0.30f,  0.05f,  0.10f,  0.15f,  0.15f,  0.10f,  0.05f, -0.30f,
	-0.30f,  0.00f,  0.15f,  0.20f,  0.20f,  0.15f,  0.00f, -0.30f,
	-0.30f,  0.05f,  0.15f,  0.20f,  0.20f,  0.15f,  0.05f, -0.30f,
	-0.30f,  0.00f,  0.10f,  0.15f,  0.15f,  0.10f,  0.00f, -0.30f,
	-0.40f, -0.20f,  0.00f,  0.00f,  0.00f,  0.00f, -0.20f, -0.40f,
	-0.50f, -0.40f, -0.30f, -0.30f, -0.30f, -0.30f, -0.40f, -0.50f,
};

// Bishops
static constexpr float white_bishop_value_table[64]
{
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
	-0.10f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.05f,  0.10f,  0.10f,  0.05f,  0.00f, -0.10f,
	-0.10f,  0.05f,  0.05f,  0.10f,  0.10f,  0.05f,  0.05f, -0.10f,
	-0.10f,  0.00f,  0.10f,  0.10f,  0.10f,  0.10f,  0.00f, -0.10f,
	-0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f, -0.10f,
	-0.10f,  0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.05f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
};
static constexpr float black_bishop_value_table[64]
{
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
	-0.10f,  0.05f,  0.00f,  0.00f,  0.00f,  0.00f,  0.05f, -0.10f,
	-0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f,  0.10f, -0.10f,
	-0.10f,  0.00f,  0.10f,  0.10f,  0.10f,  0.10f,  0.00f, -0.10f,
	-0.10f,  0.05f,  0.05f,  0.10f,  0.10f,  0.05f,  0.05f, -0.10f,
	-0.10f,  0.00f,  0.05f,  0.10f,  0.10f,  0.05f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.10f, -0.20f,
};

// Rooks
static constexpr float white_rook_value_table[64]
{
	 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,  0.00f,
	 0.05f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f,  0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	 0.00f, 0.00f, 0.00f, 0.05f, 0.05f, 0.00f, 0.00f,  0.00f,
};
static constexpr float black_rook_value_table[64]
{
	 0.00f, 0.00f, 0.00f, 0.05f, 0.05f, 0.00f, 0.00f,  0.00f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	-0.05f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, -0.05f,
	 0.05f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f, 0.10f,  0.05f,
	 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,  0.00f,
};

// Queens											
static constexpr float white_queen_value_table[64]
{
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
	-0.10f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.10f,
	-0.05f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.05f,
	 0.00f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.05f,
	-0.10f,  0.05f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.05f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
};
static constexpr float black_queen_value_table[64]
{
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
	-0.10f,  0.00f,  0.05f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.10f,  0.05f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.10f,
	 0.00f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.05f,
	-0.05f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.05f,
	-0.10f,  0.00f,  0.05f,  0.05f,  0.05f,  0.05f,  0.00f, -0.10f,
	-0.10f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f,  0.00f, -0.10f,
	-0.20f, -0.10f, -0.10f, -0.05f, -0.05f, -0.10f, -0.10f, -0.20f,
};

// Kings											
static constexpr float white_king_value_table[64]
{
	-0.40f, -0.40f, -0.35f, -0.35f, -0.35f, -0.35f, -0.40f, -0.40f,
	-0.30f, -0.30f, -0.25f, -0.25f, -0.25f, -0.25f, -0.30f, -0.30f,
	-0.30f, -0.25f, -0.10f, -0.10f, -0.10f, -0.10f, -0.25f, -0.30f,
	-0.30f, -0.25f, -0.05f, -0.05f, -0.05f, -0.05f, -0.25f, -0.30f,
	-0.25f, -0.20f,  0.00f,  0.00f,  0.00f,  0.00f, -0.20f, -0.25f,
	-0.20f, -0.15f,  0.00f,  0.05f,  0.05f,  0.00f, -0.15f, -0.20f,
	-0.05f, -0.05f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f, -0.05f,
	-0.15f,  0.00f, -0.10f, -0.15f, -0.15f, -0.10f,  0.00f, -0.15f,
};
static constexpr float black_king_value_table[64]
{
	-0.15f,  0.00f, -0.10f, -0.15f, -0.15f, -0.10f,  0.00f, -0.15f,
	-0.05f, -0.05f,  0.00f,  0.00f,  0.00f,  0.00f, -0.05f, -0.05f,
	-0.20f, -0.15f,  0.00f,  0.05f,  0.05f,  0.00f, -0.15f, -0.20f,
	-0.25f, -0.20f,  0.00f,  0.00f,  0.00f,  0.00f, -0.20f, -0.25f,
	-0.30f, -0.25f, -0.05f, -0.05f, -0.05f, -0.05f, -0.25f, -0.30f,
	-0.30f, -0.25f, -0.10f, -0.10f, -0.10f, -0.10f, -0.25f, -0.30f,
	-0.30f, -0.30f, -0.25f, -0.25f, -0.25f, -0.25f, -0.30f, -0.30f,
	-0.40f, -0.40f, -0.35f, -0.35f, -0.35f, -0.35f, -0.40f, -0.40f,
};

float vtx::Engine::static_eval(Board const& board)
{
	float evaluation = 0.0f;
	for (int i = 0; i < 64; i++)
	{
		switch (board[i].type)
		{
		case W_PAWN:
			evaluation += 1.0f;
			evaluation += white_pawn_value_table[i];
			break;

		case W_KNIGHT:
			evaluation += 3.2f;
			evaluation += white_knight_value_table[i];
			break;

		case W_BISHOP:
			evaluation += 3.3f;
			evaluation += white_bishop_value_table[i];
			break;

		case W_ROOK:
			evaluation += 5.0f;
			evaluation += white_rook_value_table[i];
			break;

		case W_QUEEN:
			evaluation += 9.0f;
			evaluation += white_queen_value_table[i];
			break;

		case W_KING:
			evaluation += 10'000.0f;
			evaluation += white_king_value_table[i];
			break;

		case B_PAWN:
			evaluation -= 1.0f;
			evaluation -= black_pawn_value_table[i];
			break;

		case B_KNIGHT:
			evaluation -= 3.2f;
			evaluation -= black_knight_value_table[i];
			break;

		case B_BISHOP:
			evaluation -= 3.3f;
			evaluation -= black_bishop_value_table[i];
			break;

		case B_ROOK:
			evaluation -= 5.0f;
			evaluation -= black_rook_value_table[i];
			break;

		case B_QUEEN:
			evaluation -= 9.0f;
			evaluation -= black_queen_value_table[i];
			break;

		case B_KING:
			evaluation -= 10'000.0f;
			evaluation -= black_king_value_table[i];
			break;
		}
	}
	return evaluation;
}
