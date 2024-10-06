#pragma once

#include "vortex/renderer.h"


namespace vtx {
    struct UI
    {
        Renderer& renderer;

        UI(Renderer& renderer);

        void update();

    private:
        void display_log_window() const;
        void display_board_window();
        void display_info_window() const;

        void load_fonts(float dpi_scaling);
        void load_colors();
    };
}
