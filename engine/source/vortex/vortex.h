#pragma once

#include "renderer/board_renderer.h"
#include "renderer/gui_renderer.h"
#include "vortex/search_info.h"
#include "engine/engine.h"


class vortex
{
    kl::window window_ = { { 1600, 900 }, "Vortex" };
    kl::gpu gpu_ = { (HWND) window_ };
    
    vtx::board_renderer board_renderer_ = { this };
    vtx::gui_renderer gui_renderer_ = { this };

    vtx::board board_ = { vtx::default_fen };
    vtx::engine engine_ = {};

    std::atomic<bool> currently_calculating_ = false;
    std::vector<search_info> search_infos_ = {};

    void play_players_turn(int clicked_index);
    void play_engines_turn();

    void on_mouse_click();
    kl::int2 get_clicked_square() const;

public:
    friend class vtx::board_renderer;
    friend class vtx::gui_renderer;

    kl::float4 background = kl::color(32, 32, 32);
    bool white_is_bottom = true;

    bool parallel_search = false;
    int search_depth = 5;

    vortex();
    ~vortex();

    void run();
};
