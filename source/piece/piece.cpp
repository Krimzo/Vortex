#include "piece/piece.h"

#include "position/position.h"


static const kl::image piece_icons[12]
{
	kl::image("resource/w_pawn.png"),
	kl::image("resource/w_knight.png"),
	kl::image("resource/w_bishop.png"),
	kl::image("resource/w_rook.png"),
	kl::image("resource/w_queen.png"),
	kl::image("resource/w_king.png"),
	kl::image("resource/b_pawn.png"),
	kl::image("resource/b_knight.png"),
	kl::image("resource/b_bishop.png"),
	kl::image("resource/b_rook.png"),
	kl::image("resource/b_queen.png"),
	kl::image("resource/b_king.png"),
};


piece::piece()
{}

piece::piece(const piece_type type)
	: type(type)
{}

const kl::image* piece::get_icon() const
{
	switch (type) {
	case w_pawn:
		return &piece_icons[0];
	case w_knight:
		return &piece_icons[1];
	case w_bishop:
		return &piece_icons[2];
	case w_rook:
		return &piece_icons[3];
	case w_queen:
		return &piece_icons[4];
	case w_king:
		return &piece_icons[5];

	case b_pawn:
		return &piece_icons[6];
	case b_knight:
		return &piece_icons[7];
	case b_bishop:
		return &piece_icons[8];
	case b_rook:
		return &piece_icons[9];
	case b_queen:
		return &piece_icons[10];
	case b_king:
		return &piece_icons[11];
	}
	return nullptr;
}

bool piece::exists() const
{
	return static_cast<bool>(type);
}

bool piece::is_white(const bool allow_none) const
{
	return (type > 64 && type < 91) || (allow_none && !type);
}

bool piece::is_black(const bool allow_none) const
{
	return (type > 96 && type < 123) || (allow_none && !type);
}

void piece::get_moves(const position& position, const int piece_index, std::vector<::position>& out_positions) const
{
	const int x = piece_index % 8;
	const int y = piece_index / 8;

	switch (type) {
	case w_pawn:
	case b_pawn:
		get_pawn_moves(position, x, y, out_positions);
		break;

	case w_knight:
	case b_knight:
		get_knight_moves(position, x, y, out_positions);
		break;

	case w_bishop:
	case b_bishop:
		get_bishop_moves(position, x, y, out_positions);
		break;

	case w_rook:
	case b_rook:
		get_rook_moves(position, x, y, out_positions);
		break;

	case w_queen:
	case b_queen:
		get_queen_moves(position, x, y, out_positions);
		break;

	case w_king:
	case b_king:
		get_king_moves(position, x, y, out_positions);
		break;
	}
}
