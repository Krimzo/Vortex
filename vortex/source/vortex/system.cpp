#include "vortex.h"


vtx::System::System()
{
	window.set_dark_mode(true);
	window.set_icon("icon/vortex.ico");
	window.on_resize.emplace_back([&](kl::Int2 size)
	{
		gpu.resize_internal(size);
		gpu.set_viewport_size(size);
	});
	window.maximize();
	if constexpr (!kl::IS_DEBUG) {
		kl::console::set_enabled(false);
	}
}

vtx::System::~System()
{
	kl::console::set_enabled(true);
}

bool vtx::System::update()
{
	timer.update_delta();
	gpu.swap_buffers(true);
	return window.process();
}
