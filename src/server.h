#pragma once

#include "memory.h"
#include "player.h"
#include "localplayer.h"
#include "offsets.hpp"
#include "cheat.h"

class Server : Cheat{
    public:
        int online_players;
        static const int MAX_PLAYERS = 63 + 1;
        Player players[MAX_PLAYERS];
        static LocalPlayer localPlayer;

        Server(uintptr_t players_address, uintptr_t localPlayer_address, const Memory *memory) : Cheat(players_address, memory){
            localPlayer = LocalPlayer(localPlayer_address, memory);
        }

        void UpdateServerData();
        static bool GetValidPlayer(Player player);
};