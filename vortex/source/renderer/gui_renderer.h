#pragma once

#include "klib.h"


class vortex;

namespace vtx {
    class gui_renderer
    {
        vortex* vortex_ = nullptr;

        bool is_viewport_focused_ = false;
        kl::int2 viewport_top_left_ = {};
        kl::int2 viewport_size_ = {};

        void display_log_window() const;
        void display_board_window();
        void display_info_window() const;

    public:
        friend class input_handler;

        gui_renderer(vortex* vortex);

        void render();
    };
}
