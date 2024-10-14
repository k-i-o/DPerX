#include "server.h"

LocalPlayer Server::localPlayer = LocalPlayer(0, nullptr);

void Server::UpdateServerData(){

    for (int i = 0; i < Server::MAX_PLAYERS; i++) { 
        this->players[i] = Player();
    }

    this->online_players = memory->Read<int32_t>(memory_address + offsets::online_players);

    if(this->online_players > 1){
        for(int i = 0; i < Server::MAX_PLAYERS; i++){
            const uintptr_t player = memory_address + (offsets::next_player * i);
            this->players[i].id = i;
            this->players[i].position = memory->Read<Vector2>(player + offsets::position);
            this->players[i].gametick = memory->Read<int32_t>(player + offsets::gametick);
            int frozen = memory->Read<int32_t>(player + offsets::frozen);
            this->players[i].frozen = frozen > 0 ? true : false;
            
            if(i == memory->Read<int32_t>(memory_address + offsets::localplayer_id)){
                Server::localPlayer.updateLocalPlayerData(this->players[i]);
            }
        }
    }

}

bool Server::GetValidPlayer(Player player){
    // return player.gametick != 0 && player.id != this->localPlayer.id && (player.id > 0 || player.id < Server::MAX_PLAYERS);
    return player.position.x != 0 && player.position.y != 0;
}