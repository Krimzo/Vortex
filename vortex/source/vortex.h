#pragma once

#include "vortex/system.h"
#include "vortex/game.h"
#include "vortex/renderer.h"
#include "vortex/ui.h"


namespace vtx {
    struct Vortex
    {
        System system;
        Game game = { system };
        Renderer renderer = { game };
        UI ui = { renderer };

        Vortex() = default;

        bool update();
    };
}
