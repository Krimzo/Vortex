#pragma once

#include "renderer/renderer.h"
#include "engine/engine.h"


class vortex
{
    int render_fps = 60;

    kl::window window_ = { { 800, 800 }, "Vortex" };
    vtx::renderer renderer_ = { window_.size() };

    vtx::board board_ = { vtx::default_fen };
    vtx::engine engine_ = {};

    std::atomic<bool> currently_calculating = false;

    void play_players_turn(int clicked_index);
    void play_engines_turn();

    void on_mouse_click();

public:
    vortex();
    virtual ~vortex();

    void run();
};
