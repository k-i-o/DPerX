#pragma once

#include "memory.h"
#include "offsets.hpp"
#include "vector2.h"
#include "localplayer.h"
#include "server.h"
#include "cheat.h"

#include <cmath>

class Aimbot : public Cheat{
    public:
        bool global_fov_enabled = false;
        bool focused_fov_enabled = false;
        bool silent_enabled = false;
        bool autofire = false;
        int autofire_distance = 100;
        bool avoid_freezed_tee = true;
        int fov_distance = 400;
        float fov_angle = 90;

        Aimbot(uintptr_t localPlayer_address, const Memory *memory) : Cheat(localPlayer_address, memory){}

        void AimTarget(Vector2 target, LocalPlayer *localPlayer);
        
        static Player GetNearestInSector(double a, int r, Server *server, bool avoid_freezed_tee = false);
        static Player GetNearestToPlayer(float maxDistance, Server *server, bool avoid_freezed_tee = false);

        static float distance(Vector2 a, Vector2 b);

};