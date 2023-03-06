#pragma once

#include "piece_type.h"
#include "klib.h"


class position;

class piece
{
public:
	piece_type type = none;

	piece();
	piece(piece_type type);

	const kl::image* get_icon() const;

	bool exists() const;
	bool is_white(bool allow_none = false) const;
	bool is_black(bool allow_none = false) const;

	void get_moves(const position& position, int piece_index, std::vector<::position>& out_positions) const;
	void get_pawn_moves(const position& position, int x, int y, std::vector<::position>& out_positions) const;
	void get_knight_moves(const position& position, int x, int y, std::vector<::position>& out_positions) const;
	void get_bishop_moves(const position& position, int x, int y, std::vector<::position>& out_positions) const;
	void get_rook_moves(const position& position, int x, int y, std::vector<::position>& out_positions) const;
	void get_queen_moves(const position& position, int x, int y, std::vector<::position>& out_positions) const;
	void get_king_moves(const position& position, int x, int y, std::vector<::position>& out_positions) const;

	static void load_icon_textures();

private:
	static kl::image icons_[12];
};
