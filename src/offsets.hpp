#pragma once

#include "game_info.hpp"

#include <cstddef>
#include <iostream>

namespace offsets {

    constexpr ptrdiff_t static_server = 0x0033DD18;
    constexpr ptrdiff_t online_players = 0x142C;
    constexpr ptrdiff_t localplayer_id = 0x1428;
    constexpr ptrdiff_t first_player = 0x1450;
    constexpr ptrdiff_t next_player = 0xF8;
    constexpr ptrdiff_t position = 0x153C;
    constexpr ptrdiff_t gametick = 0x1530;
    constexpr ptrdiff_t freezed = 0x1530;

    constexpr ptrdiff_t static_localplayer = 0x002F2D38;
    constexpr ptrdiff_t my_aim = 0x10;
    constexpr ptrdiff_t my_aim_world = 0x20;
    constexpr ptrdiff_t fire = 0x60;
    constexpr ptrdiff_t walk_left = 0xF0;
    constexpr ptrdiff_t walk_right = 0xF8;

};
