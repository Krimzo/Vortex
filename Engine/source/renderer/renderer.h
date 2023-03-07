#pragma once

#include "moves/moves.h"


namespace vtx {
    class renderer
    {
        kl::frame_buffer render_buffer_;

        void draw_square(int index, int square_size, const kl::int2& start_top_left, const kl::color& light_color, const kl::color& dark_color);
        const kl::image* get_piece_icon(const piece& piece) const;

        kl::color default_light_color = { 240, 215, 180 };
        kl::color default_dark_color = { 180, 135, 100 };
        kl::color selected_light_color = { 180, 235, 240 };
        kl::color selected_dark_color = { 100, 180, 175 };
        kl::color last_played_light_color = { 205, 240, 175 };
        kl::color last_played_dark_color = { 145, 180,  95 };
        kl::color game_over_light_color = { 240, 180, 175 };
        kl::color game_over_dark_color = { 170, 100,  90 };

        kl::image w_pawn_icon = kl::image("resource/w_pawn.png");
        kl::image w_knight_icon = kl::image("resource/w_knight.png");
        kl::image w_bishop_icon = kl::image("resource/w_bishop.png");
        kl::image w_rook_icon = kl::image("resource/w_rook.png");
        kl::image w_queen_icon = kl::image("resource/w_queen.png");
        kl::image w_king_icon = kl::image("resource/w_king.png");
        kl::image b_pawn_icon = kl::image("resource/b_pawn.png");
        kl::image b_knight_icon = kl::image("resource/b_knight.png");
        kl::image b_bishop_icon = kl::image("resource/b_bishop.png");
        kl::image b_rook_icon = kl::image("resource/b_rook.png");
        kl::image b_queen_icon = kl::image("resource/b_queen.png");
        kl::image b_king_icon = kl::image("resource/b_king.png");

    public:
        int square_size = 0;
        kl::int2 start_top_left = {};

        renderer(const kl::int2& size);
        virtual ~renderer();

        operator const kl::image& () const;

        void resize(const kl::int2& new_size);
        void render(const board& board);

        void swap();
    };
}
