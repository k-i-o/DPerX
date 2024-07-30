#include "localplayer.h"

void LocalPlayer::updateLocalPlayerData(Player me)
{
    this->id = me.id;
    this->position = me.position;
    this->gametick = me.gametick;
    this->speed = me.speed;
    this->hook_time = me.hook_time;
    this->aim = memory->Read<Vector2>(this->memory_address + variables::Offsets::my_aim);
    this->aimWorld = memory->Read<Vector2>(this->memory_address + variables::Offsets::my_aim_world);
    this->fire = memory->Read<int32_t>(this->memory_address + variables::Offsets::fire);
}