#include "moves.h"

#include "offsets.hpp"
#include "server.h"
#include "vector2.h"

void Moves::Stabilize(Player nearest){

    if(Server::localPlayer.position.x > nearest.position.x){
        memory->Write<int32_t>(memory_address + variables::Offsets::walk_right, 0);
        memory->Write<int32_t>(memory_address + variables::Offsets::walk_left, 1);
    }

    if(Server::localPlayer.position.x < nearest.position.x){
        memory->Write<int32_t>(memory_address + variables::Offsets::walk_left, 0);
        memory->Write<int32_t>(memory_address + variables::Offsets::walk_right, 1);
    }

    needReset = true;
}


void Moves::ResetWalk(){
    memory->Write<int32_t>(memory_address + variables::Offsets::walk_left, 0);
    memory->Write<int32_t>(memory_address + variables::Offsets::walk_right, 0);
    needReset = false;
}