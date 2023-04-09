#include "vortex/vortex.h"


vortex::vortex()
{
	// Window resize
	window_.on_resize.push_back([&](kl::int2 new_size)
	{
		gpu_.resize_internal(new_size);
		gpu_.set_viewport_size(new_size);
	});

	// Final
	window_.maximize();
	window_.set_icon("textures/vortex.ico");

#ifdef NDEBUG
	kl::console::set_enabled(false);
#endif
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

bool vortex::play_players_turn(const int destination_index)
{
	if (board_.get_win_state() || board_.selected_square < 0) {
		return false;
	}
	
	std::vector<vtx::board> boards = {};
	vtx::get_piece_moves(board_, board_.selected_square, boards);

	for (auto& board : boards) {
		if (destination_index == board.last_played_to) {
			board_ = board;
			return true;
		}
	}
	return false;
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
