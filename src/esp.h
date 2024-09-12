#pragma once

#include "../libs/imgui/imgui.h"
#include "cheat.h"

class ESP : Cheat{
    public:
        bool enabled = false;
        bool show_nearest = false;

        ImColor color_box = ImColor(255, 255, 255, 255);
        ImColor color_name = ImColor(255, 255, 255, 255);
        ImColor color_line = ImColor(255, 255, 255, 255);
};