#pragma once

#include "vector2.h"

class Player{
    public:
        int id;
        Vector2 position;
        Vector2 speed;
        int gametick;
        float hook_time;
        bool frozen;
        int player_size = 64;

        Player(){}
};