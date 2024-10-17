#pragma once

#include "vortex/system.h"
#include "engine/engine.h"


namespace vtx {
    struct Game
    {
        System& system;

        Board board = { vtx::default_fen };
        Engine engine;

        int search_depth = 4;
        std::vector<SearchResult> search_results;

        Game(System& system);

        void update();
        void reset();

        kl::Float2 mouse_ndc() const;

    private:
        void on_mouse_clicked();
        void on_mouse_released();

        kl::Int2 get_board_position() const;
        kl::Int2 get_board_size() const;
        kl::Int2 get_mouse_square() const;

        bool play_players_turn(int destination_index);
        void play_engines_turn();
    };
}