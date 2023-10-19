#pragma once

#include "cheat.h"
#include "vector2.h"

class Spinbot : public Cheat{
    public:

        bool enabled = false;

        float spinbotSpeed = 10.f;
        int spinbotRange = 300;
        Vector2 spinbotAngle = {0,0};
        float time = 0;

        Spinbot(uintptr_t localPlayer_address, const Memory *memory) : Cheat(localPlayer_address, memory){}

        void Rotate();
};