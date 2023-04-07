#include "renderer/renderer.h"


vtx::renderer::renderer(kl::window* window)
    : gpu_(*window)
{
	square_mesh_ = gpu_.create_screen_mesh();
	render_shaders_ = gpu_.create_render_shaders(kl::files::read_string("shaders/board_render.hlsl"));
	sampler_state_ = gpu_.create_sampler_state(true, true);

	w_pawn_icon_   = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/w_pawn.png")), nullptr);
	b_pawn_icon_   = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/b_pawn.png")), nullptr);
	w_knight_icon_ = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/w_knight.png")), nullptr);
	b_knight_icon_ = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/b_knight.png")), nullptr);
	w_bishop_icon_ = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/w_bishop.png")), nullptr);
	b_bishop_icon_ = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/b_bishop.png")), nullptr);
	w_rook_icon_   = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/w_rook.png")), nullptr);
	b_rook_icon_   = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/b_rook.png")), nullptr);
	w_queen_icon_  = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/w_queen.png")), nullptr);
	b_queen_icon_  = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/b_queen.png")), nullptr);
	w_king_icon_   = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/w_king.png")), nullptr);
	b_king_icon_   = gpu_.create_shader_view(gpu_.create_texture(kl::image("textures/b_king.png")), nullptr);
}

vtx::renderer::~renderer()
{}

void vtx::renderer::resize(const kl::int2& new_size)
{
	gpu_.resize_internal(new_size);
	gpu_.set_viewport_size(new_size);
}

void vtx::renderer::clear()
{
	gpu_.clear_internal(background_color_);
}

void vtx::renderer::render(const board& board, const bool white_is_bottom)
{
	struct vs_cb {
		kl::float4 position_data = {}; // (x_index, y_index, none, none)
		kl::float4 viewport_data = {}; // (width, height, aspect, none)
	};

	struct ps_cb {
		kl::float4 square_color = {};
	};

	gpu_.set_draw_type(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	gpu_.bind_mesh(square_mesh_, 0, 0, sizeof(kl::vertex));
	gpu_.bind_render_shaders(render_shaders_);
	gpu_.bind_sampler_state_for_pixel_shader(sampler_state_, 0);

	const kl::float2 viewport_size = gpu_.get_viewport_size();
	const float aspect_ratio = viewport_size.x / viewport_size.y;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			vs_cb vs_data = {};
			vs_data.position_data = { (float) x, (float) y, 0.0f, 0.0f };
			vs_data.viewport_data = { viewport_size, aspect_ratio, 0.0f };
			render_shaders_.vertex_shader.update_cbuffer(vs_data);

			ps_cb ps_data = {};
			ps_data.square_color = get_square_color(board, !white_is_bottom ? 7 - x : x, white_is_bottom ? 7 - y : y);
			render_shaders_.pixel_shader.update_cbuffer(ps_data);

			const auto icon_texture = get_square_icon(board, !white_is_bottom ? 7 - x : x, white_is_bottom ? 7 - y : y);
			gpu_.bind_shader_view_for_pixel_shader(icon_texture, 0);

			gpu_.draw(6, 0);
		}
	}
}

void vtx::renderer::swap()
{
	gpu_.swap_buffers(true);
}

kl::color vtx::renderer::get_square_color(const board& board, const int x, const int y) const
{
	// Single index
	const int index = x + y * 8;

	// Win states
	if (board.get_win_state() && index == board.last_played_to) {
		return ((x % 2) == (y % 2)) ? game_over_light_color_ : game_over_dark_color_;
	}

	// Possible moves
	if (board.selected_square >= 0) {
		std::vector<vtx::board> boards = {};
		get_piece_moves(board, board.selected_square, boards);
	
		for (auto& future_board : boards) {
			if (index == future_board.last_played_to) {
				return ((x % 2) == (y % 2)) ? selected_light_color_ : selected_dark_color_;
			}
		}
	}

	// Last played
	if (index == board.last_played_from || index == board.last_played_to) {
		return ((x % 2) == (y % 2)) ? last_played_light_color_ : last_played_dark_color_;
	}

	// Default colors
	return ((x % 2) == (y % 2)) ? default_light_color_ : default_dark_color_;
}

kl::dx::shader_view vtx::renderer::get_square_icon(const board& board, const int x, const int y) const
{
	switch (board(x, y)) {
	case w_pawn:
		return w_pawn_icon_;
	case b_pawn:
		return b_pawn_icon_;

	case w_knight:
		return w_knight_icon_;
	case b_knight:
		return b_knight_icon_;

	case w_bishop:
		return w_bishop_icon_;
	case b_bishop:
		return b_bishop_icon_;

	case w_rook:
		return w_rook_icon_;
	case b_rook:
		return b_rook_icon_;

	case w_queen:
		return w_queen_icon_;
	case b_queen:
		return b_queen_icon_;

	case w_king:
		return w_king_icon_;
	case b_king:
		return b_king_icon_;
	}
	return nullptr;
}
