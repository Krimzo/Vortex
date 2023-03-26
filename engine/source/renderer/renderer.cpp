#include "renderer/renderer.h"


vtx::renderer::renderer(const kl::int2& size)
    : render_buffer_(size)
{
	resize(size);
}

vtx::renderer::~renderer()
{}

vtx::renderer::operator const kl::image& () const
{
    return render_buffer_.front_buffer();
}

void vtx::renderer::resize(const kl::int2& new_size)
{
    render_buffer_.resize(new_size);
	auto& buffer = render_buffer_.front_buffer();
	
	// Square size
	square_size = (min(buffer.width(), buffer.height()) / 8);

	// Start position
	const int full_board_size = (square_size * 8);
	start_top_left = {
		(buffer.width() - full_board_size) / 2,
		(buffer.height() - full_board_size) / 2,
	};

	// Load images
	w_pawn_icon = kl::image("textures/w_pawn.png");
	w_knight_icon = kl::image("textures/w_knight.png");
	w_bishop_icon = kl::image("textures/w_bishop.png");
	w_rook_icon = kl::image("textures/w_rook.png");
	w_queen_icon = kl::image("textures/w_queen.png");
	w_king_icon = kl::image("textures/w_king.png");
	b_pawn_icon = kl::image("textures/b_pawn.png");
	b_knight_icon = kl::image("textures/b_knight.png");
	b_bishop_icon = kl::image("textures/b_bishop.png");
	b_rook_icon = kl::image("textures/b_rook.png");
	b_queen_icon = kl::image("textures/b_queen.png");
	b_king_icon = kl::image("textures/b_king.png");

	// Resize images
	w_pawn_icon.resize_scaled(kl::int2(square_size));
	w_knight_icon.resize_scaled(kl::int2(square_size));
	w_bishop_icon.resize_scaled(kl::int2(square_size));
	w_rook_icon.resize_scaled(kl::int2(square_size));
	w_queen_icon.resize_scaled(kl::int2(square_size));
	w_king_icon.resize_scaled(kl::int2(square_size));
	b_pawn_icon.resize_scaled(kl::int2(square_size));
	b_knight_icon.resize_scaled(kl::int2(square_size));
	b_bishop_icon.resize_scaled(kl::int2(square_size));
	b_rook_icon.resize_scaled(kl::int2(square_size));
	b_queen_icon.resize_scaled(kl::int2(square_size));
	b_king_icon.resize_scaled(kl::int2(square_size));
}

void vtx::renderer::render(const board& board)
{
	// Clear
	kl::image* buffer = render_buffer_.back_buffer();
	buffer->fill(kl::colors::gray);

	// Draw default colors
	for (int i = 0; i < 64; i++) {
		if (i == board.selected_square) {
			draw_square(i, square_size, start_top_left, selected_light_color, selected_dark_color);
		}
		else {
			draw_square(i, square_size, start_top_left, default_light_color, default_dark_color);
		}
	}

	// Draw last played
	if (board.last_played_from >= 0 && board.last_played_to >= 0) {
		draw_square(board.last_played_from, square_size, start_top_left, last_played_light_color, last_played_dark_color);
		draw_square(board.last_played_to, square_size, start_top_left, last_played_light_color, last_played_dark_color);
	}

	// Draw possible moves
	if (board.selected_square >= 0) {
		std::vector<vtx::board> boards = {};
		get_piece_moves(board, board.selected_square, boards);

		for (auto& future_board : boards) {
			draw_square(future_board.last_played_to, square_size, start_top_left, selected_light_color, selected_dark_color);
		}
	}

	// Draw win states
	if (board.get_win_state()) {
		draw_square(board.last_played_to, square_size, start_top_left, game_over_light_color, game_over_dark_color);
	}

	// Draw images
	for (int i = 0; i < 64; i++) {
		if (const kl::image* icon = get_piece_icon(board[i])) {
			const kl::int2 top_left = ((kl::int2(i % 8, i / 8) * square_size) + start_top_left);
			buffer->draw_image(top_left, *icon);
		}
	}
}

void vtx::renderer::swap()
{
	render_buffer_.swap();
}

void vtx::renderer::draw_square(const int index, const int square_size, const kl::int2& start_top_left, const kl::color& light_color, const kl::color& dark_color)
{
	const kl::int2 coords = { (index % 8), (index / 8) };

	kl::int2 top_left = coords * square_size;
	top_left += start_top_left;

	kl::int2 bottom_right = (coords + kl::int2(1)) * square_size - kl::int2(1);
	bottom_right += start_top_left;

	const kl::color chosen_color = ((coords.x % 2) == (coords.y % 2)) ? light_color : dark_color;

	kl::image* buffer = render_buffer_.back_buffer();
	buffer->draw_rectangle(top_left, bottom_right, chosen_color, true);
}

const kl::image* vtx::renderer::get_piece_icon(const piece& piece) const
{
	switch (piece) {
	case w_pawn:
		return &w_pawn_icon;

	case b_pawn:
		return &b_pawn_icon;

	case w_knight:
		return &w_knight_icon;

	case b_knight:
		return &b_knight_icon;

	case w_bishop:
		return &w_bishop_icon;

	case b_bishop:
		return &b_bishop_icon;

	case w_rook:
		return &w_rook_icon;

	case b_rook:
		return &b_rook_icon;

	case w_queen:
		return &w_queen_icon;

	case b_queen:
		return &b_queen_icon;

	case w_king:
		return &w_king_icon;

	case b_king:
		return &b_king_icon;
	}
	return nullptr;
}
