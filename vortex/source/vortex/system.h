#pragma once

#include "klibrary.h"


namespace vtx {
	struct System
	{
		kl::Window window = { "Vortex" };
		kl::GPU gpu = { window.ptr() };
		kl::Timer timer;

		kl::Int2 viewport_top_left;
		kl::Int2 viewport_size = { 1, 1 };
		bool viewport_focused = false;

		System();
		~System();

		bool update();
	};
}
