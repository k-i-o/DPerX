#pragma once

#include "game_info.hpp"

#include <cstddef>
#include <iostream>

namespace offsets {

    inline ptrdiff_t static_server = 0x5C1900;
    inline ptrdiff_t online_players = 0x1454;
    inline ptrdiff_t localplayer_id = 0x1450;
    inline ptrdiff_t first_player = 0x1478;
    inline ptrdiff_t next_player = 0xF8;
    inline ptrdiff_t position = 0x1480;
    inline ptrdiff_t gametick = 0x147C;
    inline ptrdiff_t frozen = 0x14CC;

    inline ptrdiff_t static_localplayer = 0x0;
    inline ptrdiff_t my_aim = 0x0;
    inline ptrdiff_t my_aim_world = 0x0;
    inline ptrdiff_t fire = 0x0;
    inline ptrdiff_t walk_left = 0x0;
    inline ptrdiff_t walk_right = 0x0;

    inline void Initialize(int client) {
        std::cout << ("Initializing offsets...") << std::endl;

        if (client == GameInfo::DDPER) {
            static_server = 0x33DD18;
            online_players = 0x142C;
            localplayer_id = 0x1428;
            first_player = 0x1450;
            next_player = 0xF8;
            position = 0x1458;
            gametick = 0x1454;
            frozen = 0x14A4;

            static_localplayer = 0x2F2CB8;
            my_aim = 0x10;
            my_aim_world = 0x20;
            fire = 0x60;
            walk_left = 0xF0;
            walk_right = 0xF8;
        } else if (client == GameInfo::DDNET) {
            static_server = 0x5C1900;
            online_players = 0x1454;
            localplayer_id = 0x1450;
            first_player = 0x1478;
            next_player = 0xF8;
            position = 0x1480;
            gametick = 0x147C;
            frozen = 0x14CC;

            static_localplayer = 0x463C20;
            my_aim = 0x10;
            my_aim_world = 0x20;
            fire = 0x60;
            walk_left = 0x100;
            walk_right = 0x108;
        }
    }
        
};
