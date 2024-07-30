#pragma once

#include "vector2.h"

class Player {
public:
    int id;
    Vector2 position;
    Vector2 speed;
    int gametick;
    float hook_time;
    bool freezed;
    int player_size;

    Player()
        : id(-1), position(), speed(), gametick(0), hook_time(0.0f), freezed(false), player_size(64) {}

    Player(int id, Vector2 position, Vector2 speed, int gametick, float hook_time, bool freezed, int player_size = 64)
        : id(id), position(position), speed(speed), gametick(gametick), hook_time(hook_time), freezed(freezed), player_size(player_size) {}
};
