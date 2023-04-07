#pragma once

#include "moves/moves.h"


namespace vtx {
    class renderer
    {
        kl::gpu gpu_ = {};

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

        kl::color        background_color_ = {  32,  32,  32 };
        kl::color     default_light_color_ = { 240, 215, 180 };
        kl::color      default_dark_color_ = { 180, 135, 100 };
        kl::color    selected_light_color_ = { 180, 235, 240 };
        kl::color     selected_dark_color_ = { 100, 180, 175 };
        kl::color last_played_light_color_ = { 205, 240, 175 };
        kl::color  last_played_dark_color_ = { 145, 180,  95 };
        kl::color   game_over_light_color_ = { 240, 180, 175 };
        kl::color    game_over_dark_color_ = { 170, 100,  90 };

        kl::color get_square_color(const board& board, int x, int y) const;
        kl::dx::shader_view get_square_icon(const board& board, int x, int y) const;

    public:
        renderer(kl::window* window);
        ~renderer();

        void resize(const kl::int2& new_size);

        void clear();
        void render(const board& board, bool white_is_bottom);
        void swap();
    };
}
