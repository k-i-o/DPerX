#pragma once

#include "game_info.hpp"

#include <cstddef>
#include <iostream>

namespace variables {

    class Offsets {
    public:
        static ptrdiff_t static_server;
        static ptrdiff_t online_players;
        static ptrdiff_t localplayer_id;
        static ptrdiff_t first_player;
        static ptrdiff_t next_player;
        static ptrdiff_t position;
        static ptrdiff_t gametick;
        static ptrdiff_t frozen;

        static ptrdiff_t static_localplayer;
        static ptrdiff_t my_aim;
        static ptrdiff_t my_aim_world;
        static ptrdiff_t fire;
        static ptrdiff_t walk_left;
        static ptrdiff_t walk_right;

        static void Initialize(int client);
    };

}
