#pragma once

#include "player.h"

#include "cheat.h"

#include <vector>

class Moves : public Cheat{
    public:

        bool enabled = false;
        bool needReset = false;

        Moves(uintptr_t players_address, const Memory *memory) : Cheat(players_address, memory){}

        void Stabilize(Player nearest);
        void Spinbot();
        void ResetWalk();

};