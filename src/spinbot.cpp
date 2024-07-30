#include "spinbot.h"

#include "offsets.hpp"

#include <cmath>
#include <iostream>

void Spinbot::Rotate(){

    spinbotAngle.x = spinbotRange * cos(spinbotSpeed * time);
    spinbotAngle.y = spinbotRange * sin(spinbotSpeed * time);

    memory->Write<Vector2>(memory_address + variables::Offsets::my_aim, spinbotAngle);

    time += 0.03f;

}