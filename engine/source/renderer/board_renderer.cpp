#include "renderer/board_renderer.h"

#include "vortex/vortex.h"


vtx::board_renderer::board_renderer(vortex* vortex)
    : vortex_(vortex)
{
	kl::gpu& gpu = vortex_->gpu_;
	render_texture_.gpu = &gpu;

	square_mesh_ = gpu.create_screen_mesh();
	render_shaders_ = gpu.create_render_shaders(kl::read_file_string("shaders/board_render.hlsl"));
	sampler_state_ = gpu.create_sampler_state(true, true);
	gpu.bind_blend_state(gpu.create_blend_state(true));

	w_pawn_icon_   = gpu.create_shader_view(gpu.create_texture(kl::image("textures/w_pawn.png")), nullptr);
	b_pawn_icon_   = gpu.create_shader_view(gpu.create_texture(kl::image("textures/b_pawn.png")), nullptr);
	w_knight_icon_ = gpu.create_shader_view(gpu.create_texture(kl::image("textures/w_knight.png")), nullptr);
	b_knight_icon_ = gpu.create_shader_view(gpu.create_texture(kl::image("textures/b_knight.png")), nullptr);
	w_bishop_icon_ = gpu.create_shader_view(gpu.create_texture(kl::image("textures/w_bishop.png")), nullptr);
	b_bishop_icon_ = gpu.create_shader_view(gpu.create_texture(kl::image("textures/b_bishop.png")), nullptr);
	w_rook_icon_   = gpu.create_shader_view(gpu.create_texture(kl::image("textures/w_rook.png")), nullptr);
	b_rook_icon_   = gpu.create_shader_view(gpu.create_texture(kl::image("textures/b_rook.png")), nullptr);
	w_queen_icon_  = gpu.create_shader_view(gpu.create_texture(kl::image("textures/w_queen.png")), nullptr);
	b_queen_icon_  = gpu.create_shader_view(gpu.create_texture(kl::image("textures/b_queen.png")), nullptr);
	w_king_icon_   = gpu.create_shader_view(gpu.create_texture(kl::image("textures/w_king.png")), nullptr);
	b_king_icon_   = gpu.create_shader_view(gpu.create_texture(kl::image("textures/b_king.png")), nullptr);
}

vtx::board_renderer::~board_renderer()
{}

void vtx::board_renderer::resize(const kl::int2& new_size)
{
	if (new_size.x <= 0 || new_size.y <= 0 || new_size == render_size_) {
		return;
	}
	render_size_ = new_size;

	kl::dx::texture_descriptor render_texture_descriptor = {};
	render_texture_descriptor.Width = render_size_.x;
	render_texture_descriptor.Height = render_size_.y;
	render_texture_descriptor.MipLevels = 1;
	render_texture_descriptor.ArraySize = 1;
	render_texture_descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	render_texture_descriptor.SampleDesc.Count = 1;
	render_texture_descriptor.Usage = D3D11_USAGE_DEFAULT;
	render_texture_descriptor.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	render_texture_.graphics_buffer = vortex_->gpu_.create_texture(&render_texture_descriptor, nullptr);
	render_texture_.create_target_view();
	render_texture_.create_shader_view();
}

void vtx::board_renderer::render(const board& board, const bool white_is_bottom)
{
	struct vs_cb {
		kl::float4   position_data = {}; // (x_index, y_index, none, none)
		kl::float4   viewport_data = {}; // (width, height, aspect, none)
		kl::float4 offset_position = {}; // (x, y, exists?, none)
	};

	struct ps_cb {
		kl::float4 square_color = {};
	};

	kl::gpu& gpu = vortex_->gpu_;

	gpu.bind_target_depth_views({ render_texture_.target_view }, nullptr);
	gpu.set_viewport_size(render_size_);
	gpu.clear_target_view(render_texture_.target_view, vortex_->background);

	gpu.set_draw_type(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gpu.bind_vertex_buffer(square_mesh_, 0, 0, sizeof(kl::vertex));

	gpu.bind_render_shaders(render_shaders_);
	gpu.bind_sampler_state_for_pixel_shader(sampler_state_, 0);

	const float aspect_ratio = (float) render_size_.x / render_size_.y;
	const UINT vertex_count = gpu.get_vertex_buffer_size(square_mesh_, sizeof(kl::vertex));

	// Render all
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			const int i = (!white_is_bottom ? 7 - x : x) + (white_is_bottom ? 7 - y : y) * 8;

			vs_cb vs_data = {};
			vs_data.position_data = { (float) x, (float) y, 0.0f, 0.0f };
			vs_data.viewport_data = { render_size_, aspect_ratio, 0.0f };
			render_shaders_.vertex_shader.update_cbuffer(vs_data);

			ps_cb ps_data = {};
			ps_data.square_color = get_square_color(board, !white_is_bottom ? 7 - x : x, white_is_bottom ? 7 - y : y);
			ps_data.square_color.w = (i == vortex_->board_.selected_square) ? 0.0f : 2.0f;
			render_shaders_.pixel_shader.update_cbuffer(ps_data);

			const auto icon_texture = get_square_icon(board, !white_is_bottom ? 7 - x : x, white_is_bottom ? 7 - y : y);
			gpu.bind_shader_view_for_pixel_shader(icon_texture, 0);

			gpu.draw(vertex_count, 0);
		}
	}

	// Rendering moving piece
	if (vortex_->board_.selected_square >= 0) {
		const int x = vortex_->board_.selected_square % 8;
		const int y = vortex_->board_.selected_square / 8;

		vs_cb vs_data = {};
		vs_data.position_data = { (float) x, (float) y, 0.0f, 0.0f };
		vs_data.viewport_data = { render_size_, aspect_ratio, 0.0f };
		vs_data.offset_position = { vortex_->mouse_ndc_, 1.0f, 0.0f };
		render_shaders_.vertex_shader.update_cbuffer(vs_data);

		ps_cb ps_data = {};
		ps_data.square_color = get_square_color(board, x, y);
		ps_data.square_color.w = 1.0f;
		render_shaders_.pixel_shader.update_cbuffer(ps_data);

		const auto icon_texture = get_square_icon(board, x, y);
		gpu.bind_shader_view_for_pixel_shader(icon_texture, 0);

		gpu.draw(vertex_count, 0);
	}
}

kl::color vtx::board_renderer::get_square_color(const board& board, const int x, const int y) const
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

kl::dx::shader_view vtx::board_renderer::get_square_icon(const board& board, const int x, const int y) const
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

void vtx::board_renderer::reset_colors()
{
	default_light_color_     = kl::color(240, 215, 180);
	default_dark_color_      = kl::color(180, 135, 100);
	selected_light_color_    = kl::color(180, 235, 240);
	selected_dark_color_     = kl::color(100, 180, 175);
	last_played_light_color_ = kl::color(205, 240, 175);
	last_played_dark_color_  = kl::color(145, 180,  95);
	game_over_light_color_   = kl::color(240, 180, 175);
	game_over_dark_color_    = kl::color(170, 100,  90);
}
