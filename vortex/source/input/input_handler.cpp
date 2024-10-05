#include "input/input_handler.h"

#include "vortex/vortex.h"


vtx::input_handler::input_handler(vortex* vortex)
    : vortex_(vortex)
{
	  vortex_->window_.mouse.left.on_press.push_back([&] { if (vortex_->gui_renderer_.is_viewport_focused_)   on_mouse_click(); });
	   vortex_->window_.mouse.left.on_down.push_back([&] { if (vortex_->gui_renderer_.is_viewport_focused_ && vortex_->board_.selected_square >= 0)    on_mouse_down(); });
	vortex_->window_.mouse.left.on_release.push_back([&] { if (vortex_->gui_renderer_.is_viewport_focused_ && vortex_->board_.selected_square >= 0) on_mouse_release(); });
}

void vtx::input_handler::on_mouse_click()
{
	const kl::int2 clicked_square = get_mouse_square();
	const int clicked_index = clicked_square.x + clicked_square.y * 8;

	if (vortex_->board_[clicked_index].is_white()) {
		vortex_->board_.selected_square = clicked_index;
	}
}

void vtx::input_handler::on_mouse_down()
{
	const kl::int2 board_position = get_board_position();
	const kl::int2 board_size = get_board_size();
	const kl::int2 current_position = vortex_->window_.mouse.position();
	
	kl::int2 position_in_viewport = current_position - board_position;
	position_in_viewport.y = board_size.y - 1 - position_in_viewport.y;

	kl::float2 ndc_position = (kl::float2) position_in_viewport / (kl::float2) board_size;
	ndc_position *= 2.0f;
	ndc_position -= kl::float2(1.0f);

	vortex_->mouse_ndc_ = ndc_position;
}

void vtx::input_handler::on_mouse_release()
{
	if (lock_.try_lock()) {
		const kl::int2 clicked_square = get_mouse_square();
		const int released_index = clicked_square.x + clicked_square.y * 8;
		const bool was_played = vortex_->play_players_turn(released_index);
		lock_.unlock();

		if (was_played) {
			std::thread([&]
			{
				lock_.lock();
				vortex_->play_engines_turn();
				vortex_->window_.notify();
				vortex_->board_.selected_square = -1;
				lock_.unlock();
			}).detach();
		}
	}
	vortex_->board_.selected_square = -1;
}

kl::int2 vtx::input_handler::get_board_position() const
{
	const kl::int2 viewport_size = vortex_->gui_renderer_.viewport_size_;
	kl::int2 top_left = vortex_->gui_renderer_.viewport_top_left_;
	if (viewport_size.x > viewport_size.y) {
		top_left.x += (viewport_size.x - viewport_size.y) / 2;
	}
	else {
		top_left.y += (viewport_size.y - viewport_size.x) / 2;
	}
	return top_left;
}

kl::int2 vtx::input_handler::get_board_size() const
{
	const kl::int2 viewport_position = vortex_->gui_renderer_.viewport_top_left_;
	const kl::int2 board_position = get_board_position();
	return vortex_->gui_renderer_.viewport_size_ - (board_position - viewport_position) * 2;
}

kl::int2 vtx::input_handler::get_mouse_square() const
{
	const kl::int2 viewport_position = vortex_->gui_renderer_.viewport_top_left_;
	const kl::int2 viewport_size = vortex_->gui_renderer_.viewport_size_;

	// Compute top left
	const kl::int2 board_position = get_board_position();
	const int square_size = min(viewport_size.x, viewport_size.y) / 8;

	// Convert mouse position
	kl::int2 clicked_square = (vortex_->window_.mouse.position() - board_position);
	clicked_square /= square_size;

	// Board flip
	if (!vortex_->white_is_bottom) {
		return kl::int2(7) - clicked_square;
	}
	return clicked_square;
}
