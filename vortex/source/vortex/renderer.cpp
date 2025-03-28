#include "vortex.h"


vtx::Renderer::Renderer(Game& game)
    : game(game), m_render_texture(game.system.gpu)
{
	kl::GPU& gpu = game.system.gpu;

	m_screen_mesh = gpu.create_screen_mesh();
	m_shaders = gpu.create_shaders(kl::read_file("resource/shaders/board_render.hlsl"));
	m_sampler_state = gpu.create_sampler_state(true, true);
	gpu.bind_blend_state(gpu.create_blend_state(true));

	w_pawn_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/W_PAWN.png")), nullptr);
	b_pawn_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/B_PAWN.png")), nullptr);
	w_knight_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/W_KNIGHT.png")), nullptr);
	b_knight_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/B_KNIGHT.png")), nullptr);
	w_bishop_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/W_BISHOP.png")), nullptr);
	b_bishop_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/B_BISHOP.png")), nullptr);
	w_rook_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/W_ROOK.png")), nullptr);
	b_rook_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/B_ROOK.png")), nullptr);
	w_queen_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/W_QUEEN.png")), nullptr);
	b_queen_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/B_QUEEN.png")), nullptr);
	w_king_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/W_KING.png")), nullptr);
	b_king_icon = gpu.create_shader_view(gpu.create_texture(kl::Image("resource/textures/B_KING.png")), nullptr);

	resize(kl::Int2(1));
}

void vtx::Renderer::update()
{
	const kl::GPU& gpu = game.system.gpu;
	kl::Int2 render_size = game.system.viewport_size;
	resize(render_size);

	gpu.bind_target_depth_views({ m_render_texture.target_view.get() }, {});
	gpu.set_viewport_size(render_size);
	gpu.clear_target_view(m_render_texture.target_view, background);

	gpu.set_draw_type(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gpu.bind_vertex_buffer(m_screen_mesh, 0, 0, sizeof(kl::Vertex));

	gpu.bind_shaders(m_shaders);
	gpu.bind_sampler_state_for_pixel_shader(m_sampler_state, 0);

	const float aspect_ratio = (float) render_size.x / (float) render_size.y;
	const UINT vertex_count = gpu.vertex_buffer_size(m_screen_mesh, sizeof(kl::Vertex));

	struct alignas(16) CB
	{
		kl::Float4 SQUARE_COLOR;
		kl::Float2 VIEWPORT_SIZE;
		kl::Float2 PIECE_INDEX;
		kl::Float2 OFFSET_POS;
		float PIECE_EXISTS;
		float ASPECT_RATIO;
	};

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			const int i = x + (7 - y) * 8;

			CB cb;
			cb.OFFSET_POS = {};
			cb.PIECE_EXISTS = 0.0f;
			cb.PIECE_INDEX = { (float) x, (float) y };
			cb.VIEWPORT_SIZE = render_size;
			cb.ASPECT_RATIO = aspect_ratio;
			cb.SQUARE_COLOR = get_square_color(game.board, x, 7 - y);
			cb.SQUARE_COLOR.w = (i == game.board.selected_square) ? 0.0f : 2.0f;
			m_shaders.upload(cb);

			kl::dx::ShaderView icon_texture = get_square_icon(game.board, x, 7 - y);
			gpu.bind_shader_view_for_pixel_shader(icon_texture, 0);

			gpu.draw(vertex_count, 0);
		}
	}

	if (game.board.selected_square >= 0) {
		const int x = game.board.selected_square % 8;
		const int y = game.board.selected_square / 8;

		CB cb;
		cb.OFFSET_POS = game.mouse_ndc();
		cb.PIECE_EXISTS = 1.0f;
		cb.PIECE_INDEX = { (float) x, (float) y };
		cb.VIEWPORT_SIZE = render_size;
		cb.ASPECT_RATIO = aspect_ratio;
		cb.SQUARE_COLOR = get_square_color(game.board, x, y);
		cb.SQUARE_COLOR.w = 1.0f;
		m_shaders.upload(cb);

		const auto icon_texture = get_square_icon(game.board, x, y);
		gpu.bind_shader_view_for_pixel_shader(icon_texture, 0);

		gpu.draw(vertex_count, 0);
	}
}

kl::Texture& vtx::Renderer::target()
{
	return m_render_texture;
}

void vtx::Renderer::reset_colors()
{
	default_light_color = kl::RGB(240, 215, 180);
	default_dark_color = kl::RGB(180, 135, 100);
	selected_light_color = kl::RGB(180, 235, 240);
	selected_dark_color = kl::RGB(100, 180, 175);
	last_played_light_color = kl::RGB(205, 240, 175);
	last_played_dark_color = kl::RGB(145, 180, 95);
	game_over_light_color = kl::RGB(240, 180, 175);
	game_over_dark_color = kl::RGB(170, 100, 90);
}

void vtx::Renderer::resize(const kl::Int2 new_size)
{
	if (m_render_texture.resolution() == new_size)
		return;

	kl::dx::TextureDescriptor render_texture_descriptor{};
	render_texture_descriptor.Width = new_size.x;
	render_texture_descriptor.Height = new_size.y;
	render_texture_descriptor.MipLevels = 1;
	render_texture_descriptor.ArraySize = 1;
	render_texture_descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	render_texture_descriptor.SampleDesc.Count = 1;
	render_texture_descriptor.Usage = D3D11_USAGE_DEFAULT;
	render_texture_descriptor.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	m_render_texture.texture = game.system.gpu.create_texture(&render_texture_descriptor, nullptr);
	m_render_texture.create_target_view();
	m_render_texture.create_shader_view();
}

kl::RGB vtx::Renderer::get_square_color(const Board& board, const int x, const int y) const
{
	const int index = x + y * 8;
	if (board.get_win_state() && index == board.last_played_to)
		return (x % 2 == y % 2) ? game_over_light_color : game_over_dark_color;

	if (board.selected_square >= 0) {
		std::vector<Board> boards;
		get_piece_moves(board, board.selected_square, boards);
		for (const auto& future_board : boards) {
			if (index != future_board.last_played_to)
				continue;
			return (x % 2 == y % 2) ? selected_light_color : selected_dark_color;
		}
	}

	if (index == board.last_played_from || index == board.last_played_to)
		return x % 2 == y % 2 ? last_played_light_color : last_played_dark_color;
	return x % 2 == y % 2 ? default_light_color : default_dark_color;
}

kl::dx::ShaderView vtx::Renderer::get_square_icon(const Board& board, const int x, const int y) const
{
	switch (board(x, y).type)
	{
	case W_PAWN: return w_pawn_icon;
	case B_PAWN: return b_pawn_icon;
	case W_KNIGHT: return w_knight_icon;
	case B_KNIGHT: return b_knight_icon;
	case W_BISHOP: return w_bishop_icon;
	case B_BISHOP: return b_bishop_icon;
	case W_ROOK: return w_rook_icon;
	case B_ROOK: return b_rook_icon;
	case W_QUEEN: return w_queen_icon;
	case B_QUEEN: return b_queen_icon;
	case W_KING: return w_king_icon;
	case B_KING: return b_king_icon;
	}
	return {};
}
