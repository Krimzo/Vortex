#include "piece/piece.h"

#include "position/position.h"


piece::piece()
{}

piece::piece(const piece_type type)
	: type(type)
{}

const kl::image* piece::get_icon() const
{
	switch (type) {
	case w_pawn:
		return (icons_ + 0);
	case w_knight:
		return (icons_ + 1);
	case w_bishop:
		return (icons_ + 2);
	case w_rook:
		return (icons_ + 3);
	case w_queen:
		return (icons_ + 4);
	case w_king:
		return (icons_ + 5);

	case b_pawn:
		return (icons_ + 6);
	case b_knight:
		return (icons_ + 7);
	case b_bishop:
		return (icons_ + 8);
	case b_rook:
		return (icons_ + 9);
	case b_queen:
		return (icons_ + 10);
	case b_king:
		return (icons_ + 11);
	}
	return nullptr;
}

bool piece::exists() const
{
	return (bool) type;
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

// static 
kl::image piece::icons_[] = {};

void piece::load_icon_textures()
{
	icons_[0] = kl::image("resource/w_pawn.png");
	icons_[1] = kl::image("resource/w_knight.png");
	icons_[2] = kl::image("resource/w_bishop.png");
	icons_[3] = kl::image("resource/w_rook.png");
	icons_[4] = kl::image("resource/w_queen.png");
	icons_[5] = kl::image("resource/w_king.png");
	icons_[6] = kl::image("resource/b_pawn.png");
	icons_[7] = kl::image("resource/b_knight.png");
	icons_[8] = kl::image("resource/b_bishop.png");
	icons_[9] = kl::image("resource/b_rook.png");
	icons_[10] = kl::image("resource/b_queen.png");
	icons_[11] = kl::image("resource/b_king.png");
}
