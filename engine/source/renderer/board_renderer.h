#pragma once

#include "moves/moves.h"


class vortex;

namespace vtx {
    class board_renderer
    {
        vortex* vortex_ = nullptr;

        kl::int2 render_size_ = {};
        kl::texture render_texture_ = { nullptr };

        kl::dx::buffer square_mesh_ = nullptr;
        kl::render_shaders render_shaders_ = {};
        kl::dx::sampler_state sampler_state_ = nullptr;

        kl::dx::shader_view   w_pawn_icon_ = nullptr;
        kl::dx::shader_view   b_pawn_icon_ = nullptr;
        kl::dx::shader_view w_knight_icon_ = nullptr;
        kl::dx::shader_view b_knight_icon_ = nullptr;
        kl::dx::shader_view w_bishop_icon_ = nullptr;
        kl::dx::shader_view b_bishop_icon_ = nullptr;
        kl::dx::shader_view   w_rook_icon_ = nullptr;
        kl::dx::shader_view   b_rook_icon_ = nullptr;
        kl::dx::shader_view  w_queen_icon_ = nullptr;
        kl::dx::shader_view  b_queen_icon_ = nullptr;
        kl::dx::shader_view   w_king_icon_ = nullptr;
        kl::dx::shader_view   b_king_icon_ = nullptr;

        kl::color get_square_color(const board& board, int x, int y) const;
        kl::dx::shader_view get_square_icon(const board& board, int x, int y) const;

    public:
        friend class vortex;
        friend class gui_renderer;

        kl::float4     default_light_color_ = kl::color(240, 215, 180);
        kl::float4      default_dark_color_ = kl::color(180, 135, 100);
        kl::float4    selected_light_color_ = kl::color(180, 235, 240);
        kl::float4     selected_dark_color_ = kl::color(100, 180, 175);
        kl::float4 last_played_light_color_ = kl::color(205, 240, 175);
        kl::float4  last_played_dark_color_ = kl::color(145, 180,  95);
        kl::float4   game_over_light_color_ = kl::color(240, 180, 175);
        kl::float4    game_over_dark_color_ = kl::color(170, 100,  90);

        board_renderer(vortex* vortex);
        ~board_renderer();

        void resize(const kl::int2& new_size);
        void render(const board& board, bool white_is_bottom);

        void reset_colors();
    };
}
