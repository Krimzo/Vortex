#pragma once

#include "klib.h"


class vortex;

namespace vtx {
    class input_handler
    {
        vortex* vortex_ = nullptr;

        std::mutex lock_ = {};

        void on_mouse_click();
        void on_mouse_down();
        void on_mouse_release();
        
        kl::int2 get_board_position() const;
        kl::int2 get_board_size() const;
        kl::int2 get_mouse_square() const;

    public:
        input_handler(vortex* vortex);
        ~input_handler();
    };
}
