#include "offsets.hpp"

namespace variables {
    ptrdiff_t Offsets::static_server = 0x0;
    ptrdiff_t Offsets::online_players = 0x0;
    ptrdiff_t Offsets::localplayer_id = 0x0;
    ptrdiff_t Offsets::first_player = 0x0;
    ptrdiff_t Offsets::next_player = 0x0;
    ptrdiff_t Offsets::position = 0x0;
    ptrdiff_t Offsets::gametick = 0x0;
    ptrdiff_t Offsets::frozen = 0x0;

    ptrdiff_t Offsets::static_localplayer = 0x0;
    ptrdiff_t Offsets::my_aim = 0x0;
    ptrdiff_t Offsets::my_aim_world = 0x0;
    ptrdiff_t Offsets::fire = 0x0;
    ptrdiff_t Offsets::walk_left = 0x0;
    ptrdiff_t Offsets::walk_right = 0x0;

    void Offsets::Initialize(int client) {
        std::cout << ("Initializing offsets...") << std::endl;

        switch (client) {
        case GameInfo::DDPER:
            static_server = 0x0033DD18;
            online_players = 0x142C;
            localplayer_id = 0x1428;
            first_player = 0x1450;
            next_player = 0xF8;
            frozen = 0x148C;
            gametick = 0x1518;
            position = 0x1524;

            static_localplayer = 0x002F2D38;
            my_aim = 0x10;
            my_aim_world = 0x20;
            fire = 0x60;
            walk_left = 0xF0;
            walk_right = 0xF8;
            break;
        case GameInfo::DDNET:
            static_server = 0x594D10;
            localplayer_id = 0x1410;
            online_players = 0x1414;
            first_player = 0x143C;
            next_player = 0xF8;
            frozen = 0x148C;
            gametick = 0x1518;
            position = 0x1524;

            static_localplayer = 0x440C20;
            my_aim = 0x10;
            my_aim_world = 0x30;
            fire = 0x70;
            walk_left = 0x100;
            walk_right = 0x108;
            break;
        }
    }
}
