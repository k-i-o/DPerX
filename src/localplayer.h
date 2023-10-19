#pragma once

#include "player.h"
#include "vector2.h"
#include "memory.h"
#include "offsets.hpp"
#include "cheat.h"

class LocalPlayer : public Player, Cheat
{
    public:
        Vector2 aim;
        Vector2 aimWorld;
        int fire;

        Player nearestPlayer = Player();

        LocalPlayer(uintptr_t localPlayer, const Memory *memory) : Cheat(localPlayer, memory){}

        LocalPlayer(){}

        void updateLocalPlayerData(Player player);
};