#pragma once

#include "renderer/renderer.h"
#include "engine/engine.h"


class vortex
{
    kl::window window_ = { { 800, 800 }, "Vortex" };
    vtx::renderer renderer_ = { &window_ };

    vtx::board board_ = { vtx::default_fen };
    vtx::engine engine_ = {};

    std::atomic<bool> currently_calculating_ = false;

    void play_players_turn(int clicked_index);
    void play_engines_turn();

    void on_mouse_click();

public:
    bool white_is_bottom = true;
    bool parallel_search = false;
    int search_depth = 5;

    vortex();
    ~vortex();

    void run();
};
