#pragma once

#include "vortex/game.h"
#include "board/moves.h"


namespace vtx {
    struct Renderer
    {
        Game& game;

        kl::Float4 background = kl::RGB(32, 32, 32);

        kl::Float4 default_light_color = kl::RGB(240, 215, 180);
        kl::Float4 default_dark_color = kl::RGB(180, 135, 100);
        kl::Float4 selected_light_color = kl::RGB(180, 235, 240);
        kl::Float4 selected_dark_color = kl::RGB(100, 180, 175);
        kl::Float4 last_played_light_color = kl::RGB(205, 240, 175);
        kl::Float4 last_played_dark_color = kl::RGB(145, 180,  95);
        kl::Float4 game_over_light_color = kl::RGB(240, 180, 175);
        kl::Float4 game_over_dark_color = kl::RGB(170, 100,  90);

        Renderer(Game& game);

        void update();

        kl::Texture& target();
        void reset_colors();

    private:
        kl::Texture m_render_texture;
        kl::dx::Buffer m_screen_mesh;
        kl::Shaders m_shaders;
        kl::dx::SamplerState m_sampler_state;
        kl::dx::ShaderView w_pawn_icon;
        kl::dx::ShaderView b_pawn_icon;
        kl::dx::ShaderView w_knight_icon;
        kl::dx::ShaderView b_knight_icon;
        kl::dx::ShaderView w_bishop_icon;
        kl::dx::ShaderView b_bishop_icon;
        kl::dx::ShaderView w_rook_icon;
        kl::dx::ShaderView b_rook_icon;
        kl::dx::ShaderView w_queen_icon;
        kl::dx::ShaderView b_queen_icon;
        kl::dx::ShaderView w_king_icon;
        kl::dx::ShaderView b_king_icon;

        void resize(kl::Int2 new_size);

        kl::RGB get_square_color(const Board& board, int x, int y) const;
        kl::dx::ShaderView get_square_icon(const Board& board, int x, int y) const;
    };
}
