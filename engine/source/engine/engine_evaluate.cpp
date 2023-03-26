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


static bool white_in_endgame(const vtx::board& board)
{
	int minor_pieces = 0;
	for (const auto piece : board.pieces) {
		switch (piece) {
		case vtx::b_queen:
			return false;

		case vtx::b_knight:
		case vtx::b_bishop:
		case vtx::b_rook:
			if (++minor_pieces > 2) {
				return false;
			}
		}
	}
	return true;
}

static bool black_in_endgame(const vtx::board& board)
{
	int minor_pieces = 0;
	for (const auto piece : board.pieces) {
		switch (piece) {
		case vtx::w_queen:
			return false;

		case vtx::w_knight:
		case vtx::w_bishop:
		case vtx::w_rook:
			if (++minor_pieces > 2) {
				return false;
			}
		}
	}
	return true;
}

void vtx::engine::static_evaluation(board& board)
{
	board.evaluation = 0.0f;

	for (int i = 0; i < 64; i++) {
		switch (board[i]) {
			// White
		case w_pawn:
			board.evaluation += 1.0f;
			board.evaluation += white_pawn_value_table[i];
			break;

		case w_knight:
			board.evaluation += 3.2f;
			board.evaluation += white_knight_value_table[i];
			break;

		case w_bishop:
			board.evaluation += 3.3f;
			board.evaluation += white_bishop_value_table[i];
			break;

		case w_rook:
			board.evaluation += 5.0f;
			board.evaluation += white_rook_value_table[i];
			break;

		case w_queen:
			board.evaluation += 9.0f;
			board.evaluation += white_queen_value_table[i];
			break;

		case w_king:
			board.evaluation += 1'000'000.0f;
			board.evaluation += white_in_endgame(board) ? white_king_end_value_table[i] : white_king_mid_value_table[i];
			break;

			// Black
		case b_pawn:
			board.evaluation -= 1.0f;
			board.evaluation -= black_pawn_value_table[i];
			break;

		case b_knight:
			board.evaluation -= 3.2f;
			board.evaluation -= black_knight_value_table[i];
			break;

		case b_bishop:
			board.evaluation -= 3.3f;
			board.evaluation -= black_bishop_value_table[i];
			break;

		case b_rook:
			board.evaluation -= 5.0f;
			board.evaluation -= black_rook_value_table[i];
			break;

		case b_queen:
			board.evaluation -= 9.0f;
			board.evaluation -= black_queen_value_table[i];
			break;

		case b_king:
			board.evaluation -= 1'000'000.0f;
			board.evaluation -= black_in_endgame(board) ? black_king_end_value_table[i] : black_king_mid_value_table[i];
			break;
		}
	}
}
