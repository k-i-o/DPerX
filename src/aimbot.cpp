#include "aimbot.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Aimbot::AimTarget(Vector2 target, LocalPlayer *localPlayer){
    target.x = target.x - localPlayer->position.x;
    target.y = target.y - localPlayer->position.y;
    memory->Write<Vector2>(memory_address + offsets::my_aim, target);

    if(autofire && distance(target, localPlayer->aim) < autofire_distance){
        memory->Write<int32_t>(memory_address + offsets::fire, localPlayer->fire + 1);
    }
}

float Aimbot::distance(Vector2 a, Vector2 b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Player Aimbot::GetNearestInSector(double a, int r, Server *server, bool avoid_freezed_tee)
{
    a = a * (M_PI / 180);

    double closestDist = 1.79769;
    Player closestPlayer = Player();

    float aAim = atan2(Server::localPlayer.aim.y, Server::localPlayer.aim.x);

    for (int i = 0; i < Server::MAX_PLAYERS; i++)
    {
        Player player = server->players[i];

        float dist = Aimbot::distance(player.position, Server::localPlayer.position);

        if (Server::GetValidPlayer(player) && player.id != Server::localPlayer.id && dist < r)
        {

            float aPlayer = atan2(player.position.y - Server::localPlayer.position.y, player.position.x - Server::localPlayer.position.x);

            if (aPlayer > aAim - (a / 2) && aPlayer < aAim + (a / 2))
            {
                
                if (dist < closestDist)
                {
                    closestDist = dist;
                    closestPlayer = player;
                }
            }
        }
    }

    Server::localPlayer.nearestPlayer = closestPlayer;

    return closestPlayer;
}

Player Aimbot::GetNearestToPlayer(float maxDistance, Server *server, bool avoid_freezed_tee)
{

    float closestDist = maxDistance;
    Player closestPlayer;

    for (int i = 0; i < Server::MAX_PLAYERS; i++)
    {
        Player player = server->players[i];

        if (player.id != Server::localPlayer.id && server->GetValidPlayer(player) && ((avoid_freezed_tee && !player.frozen) || !avoid_freezed_tee))
        {
            float dist = Aimbot::distance(player.position, Server::localPlayer.position);

            if (dist > 0 && dist < closestDist)
            {
                closestDist = dist;
                closestPlayer = player;
            }
            
        }
    }

    Server::localPlayer.nearestPlayer = closestPlayer;

    return closestPlayer;
}
