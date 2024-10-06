#include "vortex.h"


bool vtx::Vortex::update()
{
	game.update();
	renderer.update();
	ui.update();
	return system.update();
}
