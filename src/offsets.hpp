#pragma once

#include "game_info.hpp"

#include <cstddef>
#include <iostream>

namespace offsets {

    inline ptrdiff_t static_server = 0x0;
    inline ptrdiff_t online_players = 0x0;
    inline ptrdiff_t localplayer_id = 0x0;
    inline ptrdiff_t first_player = 0x0;
    inline ptrdiff_t next_player = 0x0;
    inline ptrdiff_t position = 0x0;
    inline ptrdiff_t gametick = 0x0;
    inline ptrdiff_t freezed = 0x0;

    inline ptrdiff_t static_localplayer = 0x0;
    inline ptrdiff_t my_aim = 0x0;
    inline ptrdiff_t my_aim_world = 0x0;
    inline ptrdiff_t fire = 0x0;
    inline ptrdiff_t walk_left = 0x0;
    inline ptrdiff_t walk_right = 0x0;

    inline void Initialize(int client) {
        std::cout << ("Initializing offsets...") << std::endl;

        if (client == GameInfo::DDPER) {
            static_server = 0x0033DD18;
            online_players = 0x142C;
            localplayer_id = 0x1428;
            first_player = 0x1450;
            next_player = 0xF8;
            position = 0x153C;
            gametick = 0x1530;
            freezed = 0x1508;

            static_localplayer = 0x002F2D38;
            my_aim = 0x10;
            my_aim_world = 0x20;
            fire = 0x60;
            walk_left = 0xF0;
            walk_right = 0xF8;
        } else if (client == GameInfo::DDNET) {
            static_server = 0x466CC0;
            online_players = 0x143C;
            localplayer_id = 0x1438;
            first_player = 0x1460;
            next_player = 0xF8;
            position = 0x154C;
            gametick = 0x1540;
            freezed = 0x1518;

            static_localplayer = 0x00335B80;
            my_aim = 0x10;
            my_aim_world = 0x20;
            fire = 0x60;
            walk_left = 0xF0;
            walk_right = 0xF8;
        }
    }
        
};
