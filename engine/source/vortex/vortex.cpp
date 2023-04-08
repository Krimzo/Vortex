#include "vortex/vortex.h"


vortex::vortex()
{
	// Window
	window_.on_resize.push_back([&](kl::int2 new_size)
	{
		gpu_.resize_internal(new_size);
		gpu_.set_viewport_size(new_size);
	});

	// Keyboard
	window_.keyboard.f.on_press.push_back([&]
	{
		white_is_bottom = !white_is_bottom;
	});
	window_.mouse.left.on_press.push_back([&]
	{
		std::thread(&vortex::on_mouse_click, this).detach();
	});

	// Final
	window_.maximize();
	window_.set_icon("textures/vortex.ico");
	kl::console::set_enabled(false);
}

vortex::~vortex()
{}

void vortex::run()
{
	while (window_.process()) {
		board_renderer_.render(board_, white_is_bottom);
		gui_renderer_.render();
		gpu_.swap_buffers(true);
	}
}

void vortex::on_mouse_click()
{
	// Check lock status
	if (currently_calculating_.exchange(true)) {
		return;
	}

	// Focus check
	if (!gui_renderer_.is_viewport_focused_) {
		currently_calculating_.exchange(false);
		return;
	}

	// Play turn
	const kl::int2 clicked_square = get_clicked_square();
	play_players_turn(clicked_square.x + clicked_square.y * 8);
	window_.notify();

	// Release lock
	currently_calculating_.exchange(false);
}

kl::int2 vortex::get_clicked_square() const
{
	// Compute top left
	const int square_size = min(gui_renderer_.viewport_size_.x, gui_renderer_.viewport_size_.y) / 8;
	kl::int2 start_top_left = gui_renderer_.viewport_top_left_;
	if (gui_renderer_.viewport_size_.x > gui_renderer_.viewport_size_.y) {
		start_top_left.x += (gui_renderer_.viewport_size_.x - gui_renderer_.viewport_size_.y) / 2;
	}
	else {
		start_top_left.y += (gui_renderer_.viewport_size_.y - gui_renderer_.viewport_size_.x) / 2;
	}

	// Convert mouse position
	kl::int2 clicked_square = (window_.mouse.position() - start_top_left);
	clicked_square /= square_size;

	// Board flip
	if (!white_is_bottom) {
		clicked_square = kl::int2(7) - clicked_square;
	}
	return clicked_square;
}

void vortex::play_players_turn(const int clicked_index)
{
	if (board_.get_win_state()) {
		return;
	}

	if (clicked_index == board_.selected_square) {
		board_.selected_square = -1;
		return;
	}

	if (board_[clicked_index].is_white()) {
		board_.selected_square = clicked_index;
		return;
	}

	if (board_.selected_square >= 0) {
		std::vector<vtx::board> boards = {};
		vtx::get_piece_moves(board_, board_.selected_square, boards);

		for (auto& board : boards) {
			if (clicked_index != board.last_played_to) {
				continue;
			}

			board_ = board;
			if (!board.get_win_state()) {
				play_engines_turn();
			}
			break;
		}
		board_.selected_square = -1;
	}
}

void vortex::play_engines_turn()
{
	if (board_.get_win_state()) {
		return;
	}

	board_ = engine_.find_best_board_init(board_, search_depth, parallel_search);
	
	search_info info = {};
	info.depth = engine_.get_search_depth();
	info.calls = engine_.get_call_count();
	info.time = engine_.get_search_time();
	info.eval = board_.evaluation;
	search_infos_.push_back(info);
}
